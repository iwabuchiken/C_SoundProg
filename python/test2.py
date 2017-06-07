# -*- coding: utf-8 -*-
'''
pushd C:\WORKS_2\WS\Eclipse_Luna\C_SoundProg\python
test2.py

ref : http://aidiary.hatenablog.com/entry/20110607/1307449007

'''
###############################################
import sys
sys.path.append('.')
import libs.libs as lib
# from libs.libs import *		#=> in 'libs' subdirectory --> see : https://stackoverflow.com/questions/1260792/import-a-file-from-a-subdirectory 'community wiki'
							#=> ref : http://qiita.com/Usek/items/86edfa0835292c80fff5
# from libs import *		#=> in 'libs' subdirectory --> see : https://stackoverflow.com/questions/1260792/import-a-file-from-a-subdirectory 'community wiki'
						#=> libs.py : C:\WORKS_2\WS\WS_Others\free\K6H7DD_schroedinger\28_1\libs.py

import libs.wablibs as wl
# import wablibs
# import wablibs as wl

import getopt
import os
import inspect



###############################################
import wave
import struct
import numpy as np
from pylab import *

def createSineWave (A, f0, fs, length):
	"""振幅A、基本周波数f0、サンプリング周波数 fs、
	長さlength秒の正弦波を作成して返す"""
	data = []
	# [-1.0, 1.0]の小数値が入った波を作成
	for n in arange(length * fs):  # nはサンプルインデックス
		s = A * np.sin(2 * np.pi * f0 * n / fs)
		# 振幅が大きい時はクリッピング
		if s > 1.0:  s = 1.0
		if s < -1.0: s = -1.0
		data.append(s)
	# [-32768, 32767]の整数値に変換
	data = [int(x * 32767.0) for x in data]
#	plot(data[0:100]); show()
	# バイナリに変換
	data = struct.pack("h" * len(data), *data)  # listに*をつけると引数展開される
	return data

def createSineWave_2 (A, f0, fs, length):
	"""振幅A、基本周波数f0、サンプリング周波数 fs、
	長さlength秒の正弦波を作成して返す"""
	data = []
	# [-1.0, 1.0]の小数値が入った波を作成
	for n in arange(length * fs):  # nはサンプルインデックス
		s = A * np.sin(2 * np.pi * f0 * n / fs)
		# 振幅が大きい時はクリッピング
		if s > 1.0:  s = 1.0
		if s < -1.0: s = -1.0
		data.append(s)
		
	# [-32768, 32767]の整数値に変換
	bindata = [int(x * 32767.0) for x in data]
#	plot(data[0:100]); show()
	# バイナリに変換
	bindata = struct.pack("h" * len(bindata), *bindata)  # listに*をつけると引数展開される
	
	return (data, bindata)
# 	return data

def play (data, fs, bit):
	import pyaudio
	# ストリームを開く
	p = pyaudio.PyAudio()
	stream = p.open(format=pyaudio.paInt16,
					channels=1,
					rate=int(fs),
					output= True)
	# チャンク単位でストリームに出力し音声を再生
	chunk = 1024
	sp = 0  # 再生位置ポインタ
	buffer = data[sp:sp+chunk]
	while buffer != '':
		stream.write(buffer)
		sp = sp + chunk
		buffer = data[sp:sp+chunk]
	stream.close()
	p.terminate()

if __name__ == "__main__" :
	
	
	
	freqList = [262, 294, 330, 349, 392, 440, 494, 523]  # ドレミファソラシド
	
	wflist = []
	
	timelabel = lib.get_TimeLabel_Now()
	
	for f in freqList:

		"""
		振幅A、基本周波数f0、サンプリング周波数 fs、
		長さlength秒の正弦波を作成して返す
		createSineWave (A, f0, fs, length)
		"""
		(analogdata, bindata) = createSineWave_2(1.0, f, 8000.0, 1.0)
# 		data = createSineWave(1.0, f, 8000.0, 1.0)
		
		fname = "test_2.sinewave-%d.%s.wav" % (f, timelabel)
#		 fname = "test_2.sinewave-%d.%s.wav" % (f, lib.get_TimeLabel_Now())
		
		wf = wl.WaveFile(fname)
		
		wf.samplewidth = 8000
		
		wf.binwave = bindata
		wf.analogdata = analogdata
# 		wf.binwave = data
		
# 		print "[%s:%d] fname => '%s' (nchannels = %d / samplewidth = %f)" \
# 				% (lib.thisfile(), lib.linenum(), wf.fname,\
# 				wf.nchannels, wf.samplewidth)
		
		wflist.append(wf)
		
#		 wl.save_WaveFile(fname, data)
		
#		 wl.save_WaveFile(fname)
#		 save_WaveFile(fname)
		
#		 play(data, 8000, 16)

	for wf in wflist :
		
 		print "[%s:%d] fname => '%s' (nchannels = %d / samplewidth = %f)" \
			% (lib.thisfile(), lib.linenum(), wf.fname,\
			wf.nchannels, wf.samplewidth)
		
		print "[%s:%d] data => " % (lib.thisfile(), lib.linenum())
		print wf.binwave[0:10]
		print wf.analogdata[0:10]



print "yes"
