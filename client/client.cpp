#include <fstream>
#include <string>
#include <vector>

#include <boost/tokenizer.hpp>
#include <boost/filesystem.hpp>
#include <boost/asio/ip/host_name.hpp>

#include <Ice/Ice.h>

#include <log4cxx/logger.h>

#include "flecs.h"
#include "util.h"

#define _LOG(A) LOG4CXX_INFO(logger, (A))

using namespace std;

static log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger("client"));


class FleCSClient : public Ice::Application
{
public:
    FleCSClient();

    virtual int run(int, char*[]);

private:
	void _init();
	void _load_filelist();
	void _Put(const char* obj_name);
	void _Get(const char* obj_name);
	void _RandomReadsAppends(const double r_ratio, const int runs);
	void _AppendRandom(const string& filename);

	FleCS::C2SPrx _c2s_prx;

	vector<string> _filelist;

	string _hostname;
};


FleCSClient::FleCSClient() :
    //
    // Since this is an interactive demo we don't want any signal
    // handling.
    //
    Ice::Application(Ice::NoSignalHandling)
{
	_hostname = boost::asio::ip::host_name();
}


int FleCSClient::run(int argc, char* argv[])
{
	_init();

	_RandomReadsAppends(0.1, 100);

    return EXIT_SUCCESS;
}


void FleCSClient::_init()
{
	_load_filelist();

	srandom(time(NULL));

	// init RPC proxy
	_c2s_prx = FleCS::C2SPrx::checkedCast(
			communicator()
			->propertyToProxy("FleCS_c2s.Proxy")
			->ice_twoway()
			->ice_timeout(-1)
			->ice_secure(false));
	if(!_c2s_prx)
	{
		_LOG("invalid proxy");
		exit(EXIT_FAILURE);
	}

	_LOG("Initialized.");
}


void FleCSClient::_load_filelist()
{
	const char* filename = "/usr/local/flecs/no-cnst-filelist";

	ifstream file(filename, ios::in);

	if (! file.is_open())
	{
		_LOG(string("Unable to open file ") + filename);
		exit(EXIT_FAILURE);
	}

	while (file.good())
	{
		string line;
		getline(file, line);

		if (! file.eof())
		{
			typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
			boost::char_separator<char> sep(" ");
			tokenizer tokens(line, sep);

			string filename;

			int j = 0;
			for (tokenizer::iterator i = tokens.begin(); i != tokens.end(); ++ i, ++ j)
			{
				if (j == 1)
					filename = *i;
			}

			_filelist.push_back(filename);
		}
	}

	file.close();
}


void FleCSClient::_Put(const char* obj_name)
{
	FleCS::ByteSeq content;

	_readfile(obj_name, content);

	_c2s_prx->Put(obj_name, content);
}


void FleCSClient::_Get(const char* obj_name)
{
	_LOG(obj_name);

	FleCS::ByteSeq content;
	_c2s_prx->Get(obj_name, content);

	_writefile(obj_name, content);
}


// r_ratio (read_ratio) = r / r + w. ranges [0:1].
void FleCSClient::_RandomReadsAppends(
		const double r_ratio,
		const int runs)
{
	for (int i = 0; i < runs; ++ i)
	{
		long r = random();
		char op = '-';	// 'R' or 'W'

		((double) r / RAND_MAX < r_ratio) ? op = 'R' : op = 'W';

		// pick an index of a file and filename.
		r = random();
		long idx = r % _filelist.size();
		string filename = _filelist[idx];

		switch (op)
		{
		case 'R':
			_Get(filename.c_str());
			break;

		// Note: Good to support append? FleCS would be then a file
		// store, not a key-value store. Or a key-value store with
		// append support.
		case 'W':
			_AppendRandom(filename);
			break;

		default:
			break;
		}
	}
}


void FleCSClient::_AppendRandom(const string& filename)
{
	_LOG(filename);

	// TODO: parameterize.
	const long MIN = 10;
	const long MAX = 100;

	static int seqno = 0;

	char sseqno[20];
	sprintf(sseqno, "%06d", seqno);
	++ seqno;

	// Generate random content
	FleCS::ByteSeq content;

	int cnt = _random(MIN, MAX);
	for (int i = 0; i < cnt; i ++)
	{
		content.insert(content.end(), _hostname.c_str(), _hostname.c_str() + _hostname.size());
		content.push_back('.');
		content.insert(content.end(), sseqno, sseqno + 6);
		content.push_back(' ');
	}
	content.push_back('\n');

	_c2s_prx->Append(filename, content);
}


int main(int argc, char* argv[])
{
	int rc;

	cout << "client started.\n";

	if (daemon(1, 0) == -1)
	{
		perror("daemon");
		return EXIT_FAILURE;
	}

	_LOG("Client starting...");

	try
	{
		FleCSClient app;
		rc = app.main(argc, argv, "config.client");
	}
	catch(const exception& e)
	{
		_LOG(e.what());
	}

	_LOG("Client finished.");

	return rc;
}
