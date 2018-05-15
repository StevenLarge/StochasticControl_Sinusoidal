#GNUPLOT script to plot Constant velocity ensemble results, after nondimensioanlization using k = 16 data
#Steven Large
#December 20th 2017
set term pdfcairo color enhanced font "Times-New-Roman" size 12cm, 5cm
set output "DataCompare.pdf"
set border lw 0.5
set style data l
set logscale y
set logscale x
set style circle radius graph 0.017

LMARGIN = "set tmargin at screen 0.87; set bmargin at screen 0.17; set lmargin at screen 0.100; set rmargin at screen 0.383"
MMARGIN = "set tmargin at screen 0.87; set bmargin at screen 0.17; set lmargin at screen 0.383; set rmargin at screen 0.666"
RMARGIN = "set tmargin at screen 0.87; set bmargin at screen 0.17; set lmargin at screen 0.666; set rmargin at screen 0.950"


unset key
set key off

POS = "at graph 0.15,0.85 font 'Helvetica'"

#set label 1 "Protocol duration, τ/(⟨δ{/Times-New-Roman-Italic x}^2⟩/2{/Times-New-Roman-Italic D})" at screen 0.525,0.06 center font "Times-New-Roman, 15"
set label 1 "Protocol duration τ^*" at screen 0.525,0.06 center font "Times-New-Roman, 17"
#set label 2 "Work, W/{/Times-New-Roman-Italic k}_B{/Times-New-Roman-Italic T}" at screen 0.025,0.525 center rotate by 90 font "Times-New-Roman,15"
set label 2 "Mean excess work {/Times-New-Roman-Italic ⟨W}_{ex}⟩^*" at screen 0.025,0.525 center rotate by 90 font "Times-New-Roman, 17"
#set label 3 "⟨Δλ⟩/√⟨δ{/Times-New-Roman-Italic x}^2⟩ = 2" at screen 0.2415,0.9250 center font "Times-New-Roman, 15"
set label 3 "⟨Δλ⟩^* = 2" at screen 0.2415,0.9250 center font "Times-New-Roman, 16"
set label 4 "8" at screen 0.5245,0.9250 center font "Times-New-Roman,16"
set label 5 "32" at screen 0.8075,0.9250 center font "Times-New-Roman,16"

#set label 6 "*" at screen 0.018,0.900 center font "Times-New-Roman, 15"
#set label 7 "*" at screen 0.163,0.831 center font "Times-New-Roman, 11"

#set arrow from screen 0.227,0.962 to screen 0.280,0.962 nohead lw 0.75 lc rgb "black"

#set label 6 "Total work [Eq.8]" at screen 0.71,0.300 left font "Times-New-Roman, 11"
#set label 7 "Exact solution [Eq.12]" at screen 0.71,0.220 left font "Times-New-Roman, 11"
#set arrow from screen 0.67,0.300 to screen 0.70,0.300 nohead lw 2.0 lc rgb "black"
#set arrow from screen 0.67,0.220 to screen 0.70,0.220 nohead lw 2.0 dashtype 2 lc rgb "black"



#set object circle at screen 0.140,0.835 size scr 0.001 fc rgb "black" fs transparent solid 1.0 noborder
#set label 9 "⟨δλ^2⟩^*" at screen 0.145,0.810 center font "Times-New-Roman, 13" 
#set label 10 "16" at screen 0.150,0.750 left font "Times-New-Roman, 13"
#set label 11 "4" at screen 0.150,0.710 left font "Times-New-Roman, 13"
#set label 12 "1" at screen 0.150,0.670 left font "Times-New-Roman, 13"
#set label 13 "1/4" at screen 0.150,0.630 left font "Times-New-Roman, 13"

set object circle at screen 0.247,0.800 size scr 0.001 fc rgb "black" fs transparent solid 1.0 noborder
set label 19 "⟨δλ^2⟩^*=" at screen 0.260,0.775 center font "Times-New-Roman, 13"  
set label 110 "16" at screen 0.315,0.775 center font "Times-New-Roman, 12" textcolor rgb "red"
set label 111 "4" at screen 0.315,0.640 center font "Times-New-Roman, 12" textcolor rgb "green"
set label 112 "1" at screen 0.315,0.520 center font "Times-New-Roman, 12" textcolor rgb "black"
set label 113 "1/4" at screen 0.310,0.400 center font "Times-New-Roman, 12" textcolor rgb "purple" 

#set arrow from screen 0.120,0.750 to screen 0.140,0.750 nohead lw 3.0 lc rgb "red" 
#set arrow from screen 0.120,0.710 to screen 0.140,0.710 nohead lw 3.0 lc rgb "green"
#set arrow from screen 0.120,0.670 to screen 0.140,0.670 nohead lw 3.0 lc rgb "black"
#set arrow from screen 0.120,0.630 to screen 0.140,0.630 nohead lw 3.0 lc rgb "purple"

#set label 15 "Approximation" at screen 0.410,0.750 left font "Times-New-Roman, 11"
#set label 16 "Exact" at screen 0.400,0.510 left font "Times-New-Roman, 11"
#set label 17 "solution" at screen 0.400,0.520 font "Times-New-Roman, 11"

set multiplot layout 1,3 rowsfirst

@LMARGIN
#set xrange[0.7:3000]
#set yrange[30:30000]
#set yrange[30:100000]
#set xtics format ""
#set ytics format ""
#set xtics (0.1 1, 0.3 1, 0.5 1, 0.7 1, 0.9 1, 1 0, 3 1, 5 1, 7 1, 9 1, "10^1" 10 0, 30 1, 50 1, 70 1, 90 1, 100 0, 300 1, 500 1, 700 1, 900 1, "10^3" 1000 0, 3000 1, 5000 1, 7000 1, 9000 1,"10^4" 10000 0)
#set ytics (0.1 1, 0.3 1, 0.5 1, 0.7 1, 0.9 1, "10^0" 1 0, 3 1, 5 1, 7 1, 9 1, "10^1" 10 0, 30 1, 50 1, 70 1, 90 1, "10^2" 100 0, 300 1, 500 1, 700 1, 900 1, "10^3" 1000 0, 3000 1, 5000 1, 7000 1, 9000 1,"10^4" 10000 0, 30000 1, 50000 1, 70000 1, 90000 1,100000 0)
plot "ConstantVelocityEnsemble_Dec2017/NonDimData/ConstVelTheory_L1_025_S4_NoDim.dat" with line lw 2.5 lc rgb "#70D53E4F", \
	"ConstantVelocityEnsemble_Dec2017/NonDimData/ConstVelTheory_L1_1_S4_NoDim.dat" with line lw 2.5 lc rgb "#70FC8D59", \
	"ConstantVelocityEnsemble_Dec2017/NonDimData/ConstVelTheory_L1_4_S4_NoDim.dat" with line lw 2.5 lc rgb "#7099D594", \
	"ConstantVelocityEnsemble_Dec2017/NonDimData/ConstVelTheory_L1_16_S4_NoDim.dat" with line lw 2.5 lc rgb "#703288BD", \
	"ClusterData/WorkData_May15/WorkTrend_CP1_A0_V025_NoDim.dat" using 1:2 with circles lc rgb "#D53E4F" fs transparent solid 0.5 noborder, \
	"ClusterData/WorkData_May15/WorkTrend_CP1_A0_V1_NoDim.dat" using 1:2 with circles lc rgb "#FC8D59" fs transparent solid 0.5 noborder, \
	"ClusterData/WorkData_May15/WorkTrend_CP1_A0_V4_NoDim.dat" using 1:2 with circles lc rgb "#99D594" fs transparent solid 0.5 noborder, \
	"ClusterData/WorkData_May15/WorkTrend_CP1_A0_V16_NoDim.dat" using 1:2 with circles lc rgb "#3288BD" fs transparent solid 0.5 noborder


@MMARGIN
#set xrange[0.7:3000]
#set yrange[30:30000]
#set yrange[30:100000]
#set xtics format ""
#set ytics format ""
#set xtics (0.1 1, 0.3 1, 0.5 1, 0.7 1, 0.9 1, 1 0, 3 1, 5 1, 7 1, 9 1, 10 0, 30 1, 50 1, 70 1, 90 1, 100 0, 300 1, 500 1, 700 1, 900 1, 1000 0, 3000 1, 5000 1, 7000 1, 9000 1, 10000 0)
#set ytics (0.1 1, 0.3 1, 0.5 1, 0.7 1, 0.9 1, 1 0, 3 1, 5 1, 7 1, 9 1, 10 0, 30 1, 50 1, 70 1, 90 1, 100 0, 300 1, 500 1, 700 1, 900 1, 1000 0, 3000 1, 5000 1, 7000 1, 9000 1, 10000 0, 30000 1, 50000 1, 70000 1, 90000 1,100000 0)
plot "ConstantVelocityEnsemble_Dec2017/NonDimData/ConstVelTheory_L4_025_S4_NoDim.dat" with line lw 2.5 lc rgb "#70D53E4F", \
	"ConstantVelocityEnsemble_Dec2017/NonDimData/ConstVelTheory_L4_1_S4_NoDim.dat" with line lw 2.5 lc rgb "#70FC8D59", \
	"ConstantVelocityEnsemble_Dec2017/NonDimData/ConstVelTheory_L4_4_S4_NoDim.dat" with line lw 2.5 lc rgb "#7099D594", \
	"ConstantVelocityEnsemble_Dec2017/NonDimData/ConstVelTheory_L4_16_S4_NoDim.dat" with line lw 2.5 lc rgb "#703288BD", \
	"ClusterData/WorkData_May15/WorkTrend_CP2_A0_V025_NoDim.dat" using 1:2 with circles lc rgb "#D53E4F" fs transparent solid 0.5 noborder, \
	"ClusterData/WorkData_May15/WorkTrend_CP2_A0_V1_NoDim.dat" using 1:2 with circles lc rgb "#FC8D59" fs transparent solid 0.5 noborder, \
	"ClusterData/WorkData_May15/WorkTrend_CP2_A0_V4_NoDim.dat" using 1:2 with circles lc rgb "#99D594" fs transparent solid 0.5 noborder, \
	"ClusterData/WorkData_May15/WorkTrend_CP2_A0_V16_NoDim.dat" using 1:2 with circles lc rgb "#3288BD" fs transparent solid 0.5 noborder



@RMARGIN
#set xrange[0.7:3000]
#set yrange[30:30000]
#set yrange[30:100000]
#set xtics format ""
#set ytics format ""
#set xtics (0.1 1, 0.3 1, 0.5 1, 0.7 1, 0.9 1, 1 0, 3 1, 5 1, 7 1, 9 1, 10 0, 30 1, 50 1, 70 1, 90 1, 100 0, 300 1, 500 1, 700 1, 900 1, 1000 0, 3000 1, 5000 1, 7000 1, 9000 1, 10000 0)
#set ytics (0.1 1, 0.3 1, 0.5 1, 0.7 1, 0.9 1, 1 0, 3 1, 5 1, 7 1, 9 1, 10 0, 30 1, 50 1, 70 1, 90 1, 100 0, 300 1, 500 1, 700 1, 900 1, 1000 0, 3000 1, 5000 1, 7000 1, 9000 1, 10000 0, 30000 1, 50000 1, 70000 1, 90000 1,100000 0)
plot "ConstantVelocityEnsemble_Dec2017/NonDimData/ConstVelTheory_L16_025_S4_NoDim.dat" with line lw 2.5 lc rgb "#70D53E4F", \
	"ConstantVelocityEnsemble_Dec2017/NonDimData/ConstVelTheory_L16_1_S4_NoDim.dat" with line lw 2.5 lc rgb "#70FC8D59", \
	"ConstantVelocityEnsemble_Dec2017/NonDimData/ConstVelTheory_L16_4_S4_NoDim.dat" with line lw 2.5 lc rgb "#7099D594", \
	"ConstantVelocityEnsemble_Dec2017/NonDimData/ConstVelTheory_L16_16_S4_NoDim.dat" with line lw 2.5 lc rgb "#703288BD", \
	"ClusterData/WorkData_May15/WorkTrend_CP3_A0_V025_NoDim.dat" using 1:2 with circles lc rgb "#D53E4F" fs transparent solid 0.5 noborder, \
	"ClusterData/WorkData_May15/WorkTrend_CP3_A0_V1_NoDim.dat" using 1:2 with circles lc rgb "#FC8D59" fs transparent solid 0.5 noborder, \
	"ClusterData/WorkData_May15/WorkTrend_CP3_A0_V4_NoDim.dat" using 1:2 with circles lc rgb "#99D594" fs transparent solid 0.5 noborder, \
	"ClusterData/WorkData_May15/WorkTrend_CP3_A0_V16_NoDim.dat" using 1:2 with circles lc rgb "#3288BD" fs transparent solid 0.5 noborder


unset multiplot
