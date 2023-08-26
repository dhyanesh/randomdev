#!/bin/bash

LOC1=$1
LOC2=$2

rsync -avuz $LOC1/ $LOC2 > /tmp/sync_pictures.error 2>&1
rsync -avuz $LOC2/ $LOC1 > /tmp/sync_pictures.error 2>&1
