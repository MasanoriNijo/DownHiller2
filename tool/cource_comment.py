from asyncore import write
import json
import os
from random import randint
        # case -1:
        #     return
        #     "ここからは、\n"
        #     "実際に操作して、\n"
        #     "ゴールを目指そう!\n";
        #     break;
def madeComment():
    cdir = os.path.dirname(__file__)
    file_path = cdir+"/cource_Comment.txt"
    f = open(file_path, 'w')
    for i in range(100):
      f.write("case " + str(i) + ":")
      f.write('\n')
      f.write("return" )
      f.write('\n')
      f.write("\"コメントを記入\";" )
      f.write('\n')
      f.write("break;" )
      f.write('\n')
    for i in range(100):
      f.write("case " + str(i) + ":")
      f.write('\n')
      f.write("return 0;" )
      f.write('\n')
      f.write("break;" )
      f.write('\n')
    f.close

madeComment()

