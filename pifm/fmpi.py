#!/usr/bin/env python
# coding=utf-8
import os
import time
import random
import douban
import config
import logging
import subprocess
from db import DB
from get_sogou_mp3 import getlink, get_all_mp3


class FMPI(DB):

    '''从播放队列获取歌曲并播放'''

    def play(self, name_or_url, freq=98.5, rate=44100):
        '''调用外部播放命令'''
# cmd = "mpg123 -m -C -q -s %s | sudo pifm - %s
# %s"%(name_or_url,freq,rate)
        logging.info(
            '''name_or_url: %s''' % name_or_url)
        cmd1 = "sudo mpg123 -m -C -q -s %s" % name_or_url
        cmd2 = "sudo pifm - %s %s" % (freq, rate)
        self.print_local_ip()
        logging.info(
            '''press q to play next songs,\npress Ctrl+c to terminate''')
        logging.info("")
        self.p1 = subprocess.Popen(cmd1, shell=True, stdout=subprocess.PIPE)
        self.p2 = subprocess.Popen(
            cmd2,
            shell=True,
            stdin=self.p1.stdout,
            stdout=subprocess.PIPE)
        self.p1.wait()
#        os.system(cmd)
        return 0
    def print_local_ip(self):
        cmd = "hostname -I"
        logging.info("your IP is:")
        p = subprocess.Popen(cmd,shell=True)
        p.wait()
        logging.info("Just open http://Your_IP:8080/ in broswer to add music")

    def control(self, key):
        '''has problem'''
        out, err = self.p1.communicate(key)
        return out

    def get_random_music(self):
        '''获取随机歌曲'''
        music_set = file("./music_name.txt").readlines()
        total = len(music_set)
        rand = random.randint(0, total - 1)
        return music_set[rand][:-1]

    def get_seq_music(self, index):
        '''获取随机歌曲'''
        music_set = file("./music_name.txt").readlines()
        total = len(music_set)
        index = index % total
        return music_set[index][:-1]

    def get_douban_music(self):
        '''获取豆瓣歌曲'''
        song = douban.getmusic()
        return song['title']

    def fmpi(self):
        index = 0
        '''循环检测'''
        while True:
            query = DB.getall(self)
            try:
                one = query[0]
            except:
                one = None
            os.system("clear")
            if one is not None:
                logging.info('>>>>%s' % one[1])
                if one[1].startswith('http://'):  # 直接播放url对应的音乐
                    if one[1].endswith('.mp3'):
                        self.play(one[1], config.freq, config.rate)
                    else:
                        links = get_all_mp3(one[1])
                        for i in links:
                            DB.put(self, i)
                else:
#                    url = getlink(one[1].encode('utf-8'))
#                    logging.info('url: %s' % url)
                    url = "/home/pi/music/" + one[1]
                    self.play(url, config.freq, config.rate)
#                logging.info('one[0]: %s' % one[0])
                DB.updateone(self, one[0])
            else:
                seq_music = self.get_seq_music(index)
                DB.put(self, seq_music)
                index = index + 1
#                rand_music = self.get_random_music()
#                douban_music = self.get_douban_music()
#                DB.put(self, douban_music)
            time.sleep(1)  # 降低CPU占用率
