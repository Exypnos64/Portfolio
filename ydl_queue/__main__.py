# Execute with
# $ python -m ydl_queue
# While testing:
# $ python "E:\Libraries\Desktop\Batch Files\SAO Project Shortcuts\Python Testing\ydl_queue"

import sys

if __package__ is None and not hasattr(sys, 'frozen'):
    #direct call of __main__.py
    import os.path
    path = os.path.realpath(os.path.abspath(__file__))
    sys.path.insert(0, os.path.dirname(os.path.dirname(path)))

# Keep the sys.path command until done testing and program properly installed
sys.path.append('E:\Libraries\Desktop\Batch Files\SAO Project Shortcuts\Python Testing')
import ydl_queue

# I think that this was 'proper coding', but it was making my program unnecessarily loop, so i scrapped it for no
if __name__ == '__main__':
    ydl_queue.main()
    
