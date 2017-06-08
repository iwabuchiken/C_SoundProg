# -*- coding: utf-8 -*-
'''
pushd C:\WORKS_2\WS\Eclipse_Luna\C_SoundProg\python
test.py

'''

#ref http://www.non-fiction.jp/2015/08/17/sin_wave/
import wave
import numpy as np
from matplotlib import pylab as plt
import struct

a = 1		 #振幅
fs = 8000 #サンプリング周波数
f0 = 440	#周波数
sec = 5	 #秒
 
swav=[]
 
for n in np.arange(fs * sec):
	#サイン波を生成
	s = a * np.sin(2.0 * np.pi * f0 * n / fs)
	swav.append(s)

# '''#################
#     show data
# #################'''
# for n in range(0, 10) :
#    #ref https://stackoverflow.com/questions/2960772/putting-a-variable-inside-a-string-python "answered Jun 2 '10 at 19:08"
#     print 'swav[%d] => %f' % (n, swav[n])

 
#サイン波を表示
plt.plot(swav[0:100])
plt.show()

#サイン波を-32768から32767の整数値に変換(signed 16bit pcmへ)
swav = [int(x * 32767.0) for x in swav]
 
#バイナリ化
binwave = struct.pack("h" * len(swav), *swav)
 
#サイン波をwavファイルとして書き出し
w = wave.Wave_write("output.wav")

#ref https://docs.python.jp/3/library/wave.html
#(nchannels, sampwidth, framerate, nframes, comptype, compname)
p = (1, 2, 8000, len(binwave), 'NONE', 'not compressed')

w.setparams(p)
w.writeframes(binwave)
w.close()


print "done"
