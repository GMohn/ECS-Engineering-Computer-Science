#!/usr/bin/awk
BEGIN {
	
	#
	lowest_earnings = 2^1023 
	highest_earnings = -2^1023
	#avg_earnings += $8
	#avg_withholding += $10
	#
}
NR > 1 {
	avg_earnings += $3
	avg_withholding += $4
	if ($3 <lowest_earnings)
		lowest_earnings = $3
	if ($3 >highest_earnings)
		highest_earnings = $3 }
END {avg_earnings /= NR-1
	avg_withholding /= NR-1
	{print "Average earnings: "avg_earnings"\nAverage withholding: "avg_withholding"\nLowest earnings "lowest_earnings"\nHighest earnings "highest_earnings}
}

