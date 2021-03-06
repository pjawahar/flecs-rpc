#!/bin/bash

#DATE=`date +%G%m%d`

# ssh-agent bash
# ssh-add
#
# or ssh authentication forwarding with -A

set -e
set -u

if [ $# -ne 1 ]
then
	echo "Usage: `basename $0` num_of_clients"
	exit 1
fi

hostname
date

# wait until after 10 seconds from now.
#   calc does not work with leading 0s. bc works.

CUR_TIME=`date +"%H%M%S%N"`
WAIT_UNTIL=`echo "scale=4; $CUR_TIME + 10000000000" | bc`

echo $WAIT_UNTIL

machines=( 1 2 4 5 )

for (( i=0; i<$1; i++ ))
do

HOSTNAME="polynesia"${machines[$i]}".cc.gatech.edu"

echo $HOSTNAME

ssh -A hyoon45@$HOSTNAME <<!
/dev/shm/work/flecs-rpc/misc/_run-flecs.sh $WAIT_UNTIL > /dev/null 2>&1 &
!

done

