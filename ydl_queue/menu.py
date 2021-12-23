# menu.py
# The loader and handler for the engine; the user end of the process.
# Created by: Nathan Kiehl
# Started on Fri 9/25/20

from engine import *
import traceback, os

"""
Things to Implement:
    - Menu
    - Queue of Playlists
"""

def main():
    menu()


class menu:
    @staticmethod
    def __init__():
        menu.mainDisplay()
        return
    
    @staticmethod
    def mainDisplay():
        menu = {
            's': '--YoutubeDL Menu--',
            '1': 'Start Preset Queue',
            '2': 'Start Preset Series',
            '3': 'Modify Queue',
            '4': 'Create New Preset',
            'q': 'Quit'
        }
            
        print('{menu[s]}'.format(**locals()))
        for key in menu.keys():
            if key.isnumeric():
                print('{key}) '.format(**locals()) + menu[key])
        print('q) {menu[q]}\n'.format(**locals()))
        options(input())
        
        

class options:
    @staticmethod
    def __init__(opt):
##        self.opt = opt
        method_name='opt'+str(opt)
        method=getattr(options, method_name,lambda :'Invalid')
        method()
        return
    
    @staticmethod
    def opt1():
        return
    @staticmethod
    def opt2():
        title = input("List the title of your series: ")
        eMain = engine()
        if eMain.readData(title) == 1:
            menu()
    @staticmethod
    def opt3():
        return
    @staticmethod
    def opt4():
        database.newEntry()
        input()
        menu()
        return
    @staticmethod
    def optQ():
        exit()


class database:
    @staticmethod
    def newEntry():
        title = '--['+input('Enter a title for the series: ')+']--'
        while title == '--[]--':
            print('You must supply the series a title.\n')
            title = '--['+input('Enter a title for the series: ')+']--'
            
        url = '\''+input('Enter the URL for the series: ')+'\''
        while url == '\'\'':
            print('You must supply a URL.\n')
            url = url = '\''+input('Enter the URL for the series: ')+'\''

        dirList = []
        newDir = input('Enter the directories to store the videos: ')
        while newDir == '':
            print('You must supply at least one directory.\n')
            newDir = input('Enter the directories to store the videos: ')
        while newDir != '':
            dirList.append(newDir)
            newDir = input()

        startList = []
        endList = []
        while len(endList) < len(dirList):
            startEnd = input('Enter the start and finish playlist numbers (x, y) for directory {0}: '.format(len(endList)+1))
            try:
                start, end = startEnd.strip('() ').split(',')
                startList.append(int(start))
                endList.append(int(end))
            except Exception as ex:
                print(traceback.format_exc())
                print(ex)
                print('That was not entered correctly.')

        ydl_opts = dict()
        print('Enter the Youtube-DL download options (Python versions).')
        key = input('Enter an option type: ')
        if key == '':
            print('You did not enter any options, enter a type or you will have to enter them later if you want any')
            key = input('Enter an option type: ')
        while key != '':
            value = input('Enter the option\'s value: ')
            if key != '' and value != '':
                ydl_opts[key] = value
            elif value == '':
                while value == '':
                    value = input('You did not provide a value, please enter one now: ')
            key = input('Enter an option type (none to stop): ')


        data = open(os.path.dirname(os.path.realpath(__file__))+'\Database.txt', 'a+')

        if os.path.getsize(os.path.dirname(os.path.realpath(__file__))+'\Database.txt') !=0:
            data.write('\n\n')
        data.write('{title}\n'.format(**locals()))
        data.write('Next={startList[0]}\n'.format(**locals()))
        
        data.write('Directory_List=[')
        for item in dirList:
            data.write('"' + item + '", ')
        data.seek(data.tell() - 2)
        data.truncate()
        data.write(']\n')
        
        data.write('Start_List={startList}\n'.format(**locals()))
        data.write('End_List={endList}\n'.format(**locals()))
        data.write('URL={url}\n'.format(**locals()))

        if ydl_opts:
            data.write('Download_Options=\n{\n')
            for key in ydl_opts:
                data.write('\t\'' + key + '\': \'' + ydl_opts[key] + '\',\n')
            data.seek(data.tell() - 3)
            data.truncate()
            data.write('\n}\n')
        
        data.write('--end--')
        data.close()
        
        

        print('Title = {title}'.format(**locals()))
        print('URL = {url}'.format(**locals()))
        print('startList = {startList}'.format(**locals()))
        print('endList = {endList}'.format(**locals()))

        print('dirList = ', end='')
        for item in dirList:
            print(item)
        print('ydl_opts =')
        print(ydl_opts)


##class queue:
##    def readQueue:
##
##    def reorderQueue:
##
##    def modifySeries:


        
if __name__ == '__main__':
    main()
