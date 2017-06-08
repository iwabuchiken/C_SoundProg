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
                 samplewidth=8000, framerate=None, nframes=None,\
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