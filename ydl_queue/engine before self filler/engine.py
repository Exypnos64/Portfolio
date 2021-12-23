# engine.py
# Improvement upon VRV-Dowloader that will make it easier to plug in other URLs.
# Created by: Nathan Kiehl
# Date: Wed 9/23/20

import youtube_dl, os, os.path, fileinput
#from menu import menu


class engine:
    # Set variables for chosen downloads and fix if needed
    def readData(self, titleIn):
        global inFile, title
        title = titleIn
        inFile = open(os.path.dirname(os.path.realpath(__file__))+'\Database.txt')
        line = ''

        # Read Database    
        print('Finding settings...')
        if '--[' not in title:
            title = '--['+title+']--'
        while title not in line:
            line = inFile.readline()
            if len(line) == 0:
                line = inFile.readline()
                if len(line) == 0:
                    print('There is no such series in the queue.', end='\n\n')
                    #menu()
        print('Reading information...')
        line = inFile.readline()
        while '--end--' not in line:
            self.defVars(line)
            line = inFile.readline()
        inFile.close()
        print('Settings imported')

        # Set fileLocation variable
        global fileLocation, nxtEp, section
        for i in range(0, len(endList)):
            if startList[i] <= nxtEp <= endList[i]:
                fileLocation = dirList[i]
                section = i+1

        # Update Next if out of range
        for i in endList[:-1]:
            if nxtEp == i+1:
                finish = startList[endList.index(i)+1]
                self.updtTxt()
                nxtEp = finish

        self.epCnt()


    # Sub-routine for readData() that sets variables
    def defVars(self, option):
        if 'Directory_List' in option:
##            print('Found directories')
            global dirList
            dirList = option.replace('Directory_List=[','').replace(']','').replace('"','').strip('\n').split(', ')
        elif 'Start_List' in option:
##            print('Found Start List')
            global startList
            startList = option.replace('Start_List=[','').replace(']','').split(', ')
            startList = list(map(int, startList))
        elif 'End_List' in option:
##            print('Found End List')
            global endList
            endList = option.replace('End_List=[','').replace(']','').split(', ')
            endList = list(map(int, endList))
        elif 'Next' in option:
##            print('Found Next variable')
            global nxtEp, finish
            nxtEp = int(option.replace('Next=',''))
            finish = nxtEp + 1
        elif 'URL' in option:
##            print('Found URL')
            global url
            url = option.replace('URL=','').replace("'",'')
        elif 'Download_Options' in option:
##            print('Found Download Options')
            global ydl_opts
            ydl_opts = dict()
            inFile.readline()
            key, value = inFile.readline().replace('\'','').strip(',\n').strip('\n').strip('\t').split(': ')
            while '}' not in key:
                ydl_opts[key] = value
                opt = inFile.readline().replace('"','').strip(',\n').strip('\n').strip('\t')
                if len(opt.split(': ')) == 2:
                    key, value = opt.split(': ')
                else:
                    break
        else:
            print('Unknown option found')
        

    # Counts files in specified directory
    def epCnt(self):
        print('Counting files...')
        global playNum, epNum
        epNum = len([name for name in os.listdir(fileLocation) if os.path.isfile(os.path.join(fileLocation, name)) and not 'fdash' in name])
        playNum = epNum + startList[dirList.index(fileLocation)]
        self.epMch(finish)
        

    # Checks if selected video completed download
    def epMch(self, finish):
        if playNum == finish:
            print('Section {section} Match: Video {epNum} download complete'.format(**globals()))
            self.updtTxt()
            
            # If only one video was desired for this run
            if repeat == False:
                input()
                exit()
            self.readData()
        else:
            self.epCall()

    # Updates 'Next' option in database for selected playlist
    def updtTxt(self):
        # Locates Database.txt next to this file
        filename = os.path.dirname(os.path.realpath(__file__))+'\Database.txt'

        # Re-Writes entire file to update one line
        with fileinput.FileInput(filename, inplace=True) as file:
            found = False
            for line in file:
                # When under desired playlist
                if found == True:
                    if 'Next=' in line:
                        print(line.replace('Next='+str(nxtEp), 'Next='+str(finish)), end='')
                        found == False
                    else:
                        print(line, end='')
                # Indicates desired playlist
                elif title in line:
                    print(line, end='')
                    found = True
                # Everywhere else
                else:
                    print(line, end='')
            file.close()
                

    # Informs user of the episode number being obtained
    def epCall(self):
        global epNum, section
        for i in endList:
            if nxtEp <= i:
                epNum = finish - startList[endList.index(i)]
                print('Obtaining Section {section} Episode {epNum}'.format(**globals()))
                print()
                self.dlEngine()
                exit()

        input('No more episodes left to download.')
        exit()


    # Downloads video using Youtube-DL with specified URL and options
    def dlEngine(self):
        global url
        for i in endList:
            if nxtEp <= i:
                os.chdir(dirList[endList.index(i)])

                with youtube_dl.YoutubeDL(ydl_opts) as ydl:
                    ydl.download([url])
                print()
                self.epCnt()
                exit()
        print('The engine found no more episodes to download')
        exit()    
