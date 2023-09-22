#!/usr/bin/bash

payroll_file=$1

###########################################################
# Phase 1
###########################################################

awk_code='{print $3","$4","$8+$11 ","$10 }' # awk command here
#field_seperator_1='' # What should the feel seperator be?
awk -F "," "$awk_code" "$payroll_file" > w2_info

###########################################################
# Phase 2
###########################################################

#field_seperator_2=',' # What should this field seperator be? 
awk -F "," -f data_aggregator.awk < w2_info > agg_data
