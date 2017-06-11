if (exist("n") == 0 || n < 0) n = 0 #変数の初期化

set sample 500

set grid lw 1

unset key

a = 4

set xrange[-pi*a:pi*a]; set yrange[-3:3]

s_title = sprintf("sum of sin(x + 1) --- sin(x + %d)", n)
set title s_title

n_max = 60
#wait = 0.2
wait = 0.0

dname_images = "images_20170610_115547"

outfile(n) = sprintf("images/%s/%03d.jpg", dname_images, n)  #出力ファイル名
#outfile(n) = sprintf("%s/%03d.jpg", dname_images, n)  #出力ファイル名

set terminal jpeg  enhanced font "Times" 15 size 600, 600
#set terminal jpeg  enhanced font "Times" 20 size 600, 600

set output outfile(n)

###### plot
plot for[j=1 : n] sum[i=1:j] sin(x + i)
#plot sum[i=1:n] sin(x + i)
#plot sin(x + n)



if (n < n_max)  pause wait; n = n + 1; unset label; reread

n = 0
