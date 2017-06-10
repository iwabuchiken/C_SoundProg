if (exist("n") == 0 || n < 0) n = 1 #•Ï”‚Ì‰Šú‰»

a = 3
set xrange[-pi*a:pi*a]; set yrange[-a : a]

set grid lw 1

unset key

set sample 500

max = n
#max = 100

str_title = sprintf("sum of sin(x + 1) ~ sin(x + %d)", max)
set title str_title

plot for[j=1 : max] sum[i=1:j] sin(x + i) 
#plot for[j=1 : 100] sum[i=1:j] sin(x + i) 


n_max = max
wait = 0.1

if (n < n_max)  pause wait; n = n + 1; unset label; reread

n = 0
