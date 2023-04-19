#!/bin/bash
#==============================================================================#
#
#   FILE: fq.sh
#                   
#   USAGE: ./fq.sh <ip addr>
#                   
#   DESCRIPTION: Script to parse zeek logs for information on an IP address
#
#   AUTHOR: ActiveCounterMeasures team
#   CREATED: --
#   MODIFIED: --
#   VERSION: 1.0
#
#   LICENSE: See ACM
#==============================================================================#

echo '===================='
echo '===== DNS INFO ====='
echo '===================='
cat dns.* | zeek-cut answers query | sort | uniq | grep -Fw "$1"
echo '####################'
echo '##### TLS INFO #####'
echo '####################'
cat ssl.* | zeek-cut id.resp_h server_name validation_status | sort | uniq | grep -Fw "$1"

