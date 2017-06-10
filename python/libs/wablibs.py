# -*- coding: utf-8 -*-

###############################################
import sys
sys.path.append('.')
from libs import *
# from libs.libs import *

import getopt
import os
import inspect
###############################################


import wave
import struct
import numpy as np
from time import sleep

EQUAL_TEMPERAMENTS = [1.000000,
            1.059463,
            1.122462,
            1.189207,
            1.259921,
            1.334840,
            1.414214,
            1.498307,
            1.587401,
            1.681793,
            1.781797,
            1.887749,
            2.000000]



'''
    @param
    binwave    => binwave = struct.pack("h" * len(swav), *swav) : C:\WORKS_2\WS\Eclipse_Luna\C_SoundProg\python\test.py
'''
def save_WaveFile(fname, binwave, comptype='NONE', compname='not compressed'):
    
    '''###################
        validate: dir exists        
    ###################'''
    dpath = os.path.dirname(fname)
    
    #ref http://maku77.github.io/python/create-directory.html
    if not os.path.exists(dpath) : 
        os.makedirs(dpath, True)
        print "[%s:%d] dir created => '%s'" % (thisfile(), linenum(), dpath)

    
    
    w = wave.Wave_write(fname)
# 	w = wave.Wave_write("output.wav")
    
    p = (1, 2, 8000, len(binwave), comptype, compname)
# 	p = (1, 2, 8000, len(binwave), 'NONE', 'not compressed')
    
    
    w.setparams(p)
    
    w.writeframes(binwave)
    
    w.close()

# def copy_WaveFile(binwave):
    
#ref https://en.wikibooks.org/wiki/A_Beginner%27s_Python_Tutorial/Classes

def save_WaveFile__Class(wavefile, fname_dst = '', dpath_dst=''):
    
    #debug
    print "[%s:%d] fname_dst = '%s' || dpath_dst = '%s'" \
            % (thisfile(), linenum(), fname_dst, dpath_dst)
            #=> fname_dst = 'audio' || dpath_dst = ''
    
    print "[%s:%d] wavefile.fname => '%s'" % (thisfile(), linenum(), wavefile.fname)
            #=> 'test_2.sinewave-262.20170607_165720.wav'

    '''###################
        data
    #####################'''
    comptype = wavefile.comptype
    compname = wavefile.compname
    
    if comptype == None or comptype == '' : comptype = 'NONE'
    if compname == None or compname == '' : compname = 'not compressed'
    
    binwave = wavefile.bindata
    
    fname = ''
    dpath = ''
    
    ### file name
    if fname_dst == '' : fname = wavefile.fname
    else : fname = fname_dst

    ### dir path
    if dpath_dst == '' : dpath = wavefile.dpath
    else : dpath = dpath_dst
    
    ### build : file full path
    fpath = "%s/%s" % (dpath, fname)

    #debug
    print "[%s:%d] fpath => '%s'" % (thisfile(), linenum(), fpath)
    

    '''###################
        save
    #####################'''
    save_WaveFile(fpath, binwave, comptype, compname)
#     save_WaveFile(fname, binwave, comptype, compname)
    
    
# def copy_WaveFile(binwave):
    
#ref https://en.wikibooks.org/wiki/A_Beginner%27s_Python_Tutorial/Classes

class WaveFile :
    
#     def __init__(self, fname = '', bindata = None, nchannels = 1) :    #=> works
    def __init__(self, fname = '', dpath = '',\
                 bindata = None, nchannels=1,\
                 samplewidth=8000, basefreq=None,\
                 framerate=None, nframes=None,\
                 comptype=None, compname=None, analogdata = None) :
        
        self.fname = fname
        self.dpath = dpath
        
        self.bindata = bindata
        self.nchannels  = nchannels
        self.samplewidth    = samplewidth
        self.framerate=framerate
        self.nframes=nframes
        self.comptype   = comptype
        self.compname   = compname
        self.analogdata   = analogdata
        
        self.basefreq   = basefreq
        
        

def copy_WaveFile(wavefile_src, fname_new=''):
    
    wf = WaveFile()
    
    if fname_new == '' :
        
        #ref https://stackoverflow.com/questions/541390/extracting-extension-from-filename-in-python/ 'answered Feb 12 '09 at 14:12'
        fname_trunk, fname_ext = os.path.splitext(wavefile_src.fname)
        
        wf.fname = "%s.%s%s" % (fname_trunk, "copy", fname_ext)
#         wf.fname = "%s.%s.%s" % (fname_trunk, "copy", fname_ext)
    
    else :
        
        wf.fname = fname_new
        
#     wf.fname = wavefile_src.fname
        
    wf.dpath = wavefile_src.dpath
    wf.bindata = wavefile_src.bindata
    wf.nchannels  = wavefile_src.nchannels
    wf.samplewidth    = wavefile_src.samplewidth
    wf.framerate= wavefile_src.framerate
    wf.nframes= wavefile_src.nframes
    wf.comptype   = wavefile_src.comptype
    wf.compname   = wavefile_src.compname
    wf.analogdata   = wavefile_src.analogdata

    return wf
'''###################
ref : http://floor13.sakura.ne.jp/book03/book03.html
#####################'''
def createSineWave (A, f0, fs, length):
    """�U��A�A��{���g��f0�A�T���v�����O���g�� fs�A
    ����length�b�̐����g���쐬���ĕԂ�"""
    data = []
    radians = []
    
    # [-1.0, 1.0]�̏����l���������g���쐬
    for n in np.arange(length * fs):  # n�̓T���v���C���f�b�N�X
#     for n in arange(length * fs):  # n�̓T���v���C���f�b�N�X
        
        radian = 2 * np.pi * f0 * n / fs
        
        s = A * np.sin(radian)
#         s = A * np.sin(2 * np.pi * f0 * n / fs)
        # �U�����傫�����̓N���b�s���O
        if s > 1.0:  s = 1.0
        if s < -1.0: s = -1.0
        
        data.append(s)
        
        radians.append(radian)
        
    # [-32768, 32767]�̐����l�ɕϊ�
    bindata = [int(x * 32767.0) for x in data]
#    plot(data[0:100]); show()
    # �o�C�i���ɕϊ�
    bindata = struct.pack("h" * len(bindata), *bindata)  # list��*������ƈ����W�J�����
    
    return (data, bindata, radians)
#     return (data, bindata)
#     return data

#]]createSineWave (A, f0, fs, length)

'''
<Usage>
get_WaveFile__Sines("out.wav", A = 1.0, 262, 8000, length = 1.0, phase = 1.0)
'''
def get_WaveFile__Sines (fname, A, f0, fs, length = 1.0, phase = 1.0, type = "sine"):
# def get_WaveFile__Sines (fname, A, f0, fs, length = 1.0, phase = 1.0):
# def get_WaveFile__Sines (fname, A, f0, fs, length, phase = 1.0):
    
    '''###################
        prep : data        
    ###################'''
    
    
    data = []
    radians = []
    
    # [-1.0, 1.0]�̏����l���������g���쐬
    if type == "sine" :
        for n in np.arange(length * fs):  # n�̓T���v���C���f�b�N�X
    #     for n in arange(length * fs):  # n�̓T���v���C���f�b�N�X
            
            radian = 2 * np.pi * f0 * n * phase / fs
    #         radian = 2 * np.pi * f0 * n / fs
            
            s = A * np.sin(radian)
    #         s = A * np.sin(2 * np.pi * f0 * n / fs)
            # �U�����傫�����̓N���b�s���O
            if s > 1.0:  s = 1.0
            if s < -1.0: s = -1.0
            
            data.append(s)
            
            radians.append(radian)
    elif type == "cosine" :
        for n in np.arange(length * fs):  # n�̓T���v���C���f�b�N�X
    #     for n in arange(length * fs):  # n�̓T���v���C���f�b�N�X
            
            radian = 2 * np.pi * f0 * n * phase / fs
    #         radian = 2 * np.pi * f0 * n / fs
            
            s = A * np.cos(radian)
    #         s = A * np.sin(2 * np.pi * f0 * n / fs)
            # �U�����傫�����̓N���b�s���O
            if s > 1.0:  s = 1.0
            if s < -1.0: s = -1.0
            
            data.append(s)
            
            radians.append(radian)
    else :
        
        print "[%s:%d] Unknown trig name => '%s'" % (thisfile(), linenum(), type)
        
        return None
    
        
    # [-32768, 32767]�̐����l�ɕϊ�
    bindata = [int(x * 32767.0) for x in data]
#    plot(data[0:100]); show()
    # �o�C�i���ɕϊ�
    bindata = struct.pack("h" * len(bindata), *bindata)  # list��*������ƈ����W�J�����
    
    '''###################
        build : wavefile        
    ###################'''
    wf = WaveFile(fname)
    
    wf.nchannels  = 1
    wf.samplewidth    = fs
#     wf.framerate=framerate
#     wf.nframes=nframes
#     wf.comptype   = wavefile_src.comptype
#     wf.compname   = wavefile_src.compname
    wf.analogdata   = data
    wf.bindata = bindata
    wf.radians = radians

    wf.basefreq = f0
    
    '''###################
        return        
    ###################'''
    return wf
    
#     return (data, bindata, radians)
#     return (data, bindata)
#     return data

#]]createSineWave (A, f0, fs, length)

def get_WaveFile__AnalogData (\
              fname, analogdata, \
              A, length, \
              nchannels = 1, radians = None, \
              f0 = None, fs = None):
    
    '''###################
        prep : data        
    ###################'''
    
    # [-32768, 32767]�̐����l�ɕϊ�
    bindata = [int(x * 32767.0) for x in analogdata]
#    plot(data[0:100]); show()
    # �o�C�i���ɕϊ�
    bindata = struct.pack("h" * len(bindata), *bindata)  # list��*������ƈ����W�J�����
    
    '''###################
        build : wavefile        
    ###################'''
    wf = WaveFile(fname)
    
    wf.nchannels  = nchannels
#     wf.nchannels  = 1
    wf.samplewidth    = fs
    
    wf.analogdata   = analogdata
    
    wf.bindata = bindata
    wf.radians = radians

    wf.basefreq = f0
    
    '''###################
        return        
    ###################'''
    return wf
#]]get_WaveFile__AnalogData


'''
    <function>
    Volume down the analogdata values by val / 1000
'''
def amplitude_Down(wavefile, val) :
    
    baseval = 1000
    
    wavefile.analogdata = [ wavefile.analogdata[i] * \
                            val / 1000.0 for i in range(len(wavefile.analogdata))]
    
    wavefile.bindata = [int(x * 32767.0) for x in wavefile.analogdata]
    
    wavefile.bindata = struct.pack("h" * len(wavefile.bindata), *wavefile.bindata)

    return wavefile
    
def data_Absolutize(wavefile, generate_new = False, fname = '') :
# def data_Absolutize(wavefile, generate_new = True, fname = '') :
    
    ###################
    #    init : wf        
    #####################
    wf = None
    
    if generate_new == True : wf = wl.WaveFile()
    else : wf = wavefile

    ###################
    #    absolutize : analog    
    #####################
    print "[%s:%d] len(wf.analogdata) => %d" % (thisfile(), linenum(), len(wf.analogdata))
                        
    length = len(wf.analogdata)
                        
    wf.analogdata = [math.fabs(wf.analogdata[i]) for i in range(len(wf.analogdata))]
#     wf.analogdata = [math.fabs(wf.analogdata[i]) for i in wf.analogdata]
                        
#     for i in range(length) :
#         
#         wf.analogdata[i] = math.fabs(wf.analogdata[i])
        
    ###################
    #    absolutize : binary    
    #####################
    wf.bindata = [int(x * 32767.0) for x in wf.analogdata]
    
    wf.bindata = struct.pack("h" * len(wf.bindata), *wf.bindata)
        
    '''###################
        return        
    ###################'''
    return wf
    
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
    
'''
get_SineWF(A, f0, fs = 8000.0, phase=1.0, length=1.0, dpath = "audio", fname='')
    Example : A note
    get_SineWF(1.0, 262, fs = 8000.0, phase=1.0, length=1.0, dpath = "audio", fname='')
'''
def get_SineWF(A, f0, fs = 8000.0, phase=1.0, length=1.0, dpath = "audio", fname=''):
    
    timelabel = get_TimeLabel_Now()

    ### param : data
    (analogdata, bindata, radians) = createSineWave(A, f0, fs, length)
    
    if fname == '' : fname = "sinewavefile.%s.wav" % (timelabel)
    
    fpath = "%s/%s" % (dpath, fname)

    '''###################
            build : wavefile        
        ###################'''
    wf = get_WaveFile__Sines(fname, A, f0, fs, length, phase = 1.0)
    
#     save_WaveFile__Class(wf, dpath_dst=dpath)

#     print "[%s:%d] file saved => '%s'" % (thisfile(), linenum(), fname)
    
    return wf
    
