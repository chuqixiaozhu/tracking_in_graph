#set terminal pdfcairo enhanced font "Times New Roman, 20"
#set output "20_hole_vs_vt.pdf"
#set terminal postscript eps color solid font "Times New Roman, 20"
set terminal postscript eps color solid enhanced font ", 24"
#set terminal emf color solid enhanced font "Times New Roman, 20"
set output "m_num_vs_tmd.eps"
#set terminal qt font "Times New Roman, 20"
#set xlabel "{/SimSun=20 �ն�����}"
set xlabel "Number of Mobile Nodes"
set xrange [1:20]
set xtics 5
set mxtics 1
#set ylabel "{/SimSun=20 ��Ч���ʱ���� (%)}"
set ylabel "Moving Distance Ratio (%)"
set yrange [0:100]
set ytics 20
set mytics 1
#set format y "%.1f"
set grid
set key box
set key Left
#set key width 10
#set key spacing 10
# set key left bottom at 2, 2
#plot "m_num-m_vs_tmd" u 1:($2/1000.0) w lp lt 1 lw 2 pt 5 ps 2 title "Expects", "m_num-f_vs_tmd" u 1:($2/1000.0) w lp lt 2 lw 2 pt 2 ps 2 title "FT", "m_num-exp_vs_tmd.txt" u 1:($2*100.0) w lp lt 3 lw 2 pt 3 ps 2 title "MFT", "m_num-c_vs_tmd" u 1:($2/1000.0) w lp lt 4 lw 2 pt 4 ps 2 title "CT"
plot "m_num-exp_vs_tmd.txt" u 1:($2*100.0) w lp lt 1 lw 2 pt 5 ps 2 title "Expects", \
     "m_num-wait_vs_tmd.txt" u 1:($2*100.0) w lp lt 2 lw 2 pt 2 ps 2 title "Wait"
set output
#!pdftops -eps 20_hole_vs_vt.pdf