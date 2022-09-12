from asyncore import write
import json
import os
from random import randint

def madeCourceC(json_data):
    minLengh = json_data["madePrm"]["minLengh"]
    maxLength = json_data["madePrm"]["maxLength"]
    minDeg = json_data["madePrm"]["minDeg"]
    maxDeg = json_data["madePrm"]["maxDeg"]
    diffPrm = json_data["madePrm"]["diffPrm"]
    courceR = 0
    courceLength = 0
    beforeDeg = 0

    cdir = os.path.dirname(__file__)
    file_path = cdir+"/courceC_prm.txt"
    f = open(file_path, 'w')
    # _c->dC(100,-35 + kaku);
    for i in range(20):
      courceLength = randint(minLengh, maxLength)
      courceDeg = randint(min(beforeDeg + diffPrm,maxDeg), maxDeg) if i%2 else randint(minDeg, max(beforeDeg-diffPrm,minDeg))
      diffDeg = courceDeg - beforeDeg
      beforeDeg = courceDeg
      courceR = int(abs(courceLength/(3.14 * (diffDeg/180))))
      f.write(json_data["funcSt"]+str(courceR)+", "+str(courceDeg)+json_data["funcEd"])
      f.write('\n')

    f.close

def madeCourceK(json_data):
    minLengh = json_data["madePrm"]["minLengh"]
    maxLength = json_data["madePrm"]["maxLength"]
    minDeg = json_data["madePrm"]["minDeg"]
    maxDeg = json_data["madePrm"]["maxDeg"]
    diffPrm = json_data["madePrm"]["diffPrm"]
    courceR = 0
    courceLength = 0
    beforeDeg = 0

    cdir = os.path.dirname(__file__)
    file_path = cdir+"/courceK_prm.txt"
    f = open(file_path, 'w')
    # _c->dC(100,-35 + kaku);
    for i in range(20):
      courceLength = randint(minLengh, maxLength)
      courceDeg = randint(min(beforeDeg + diffPrm,maxDeg), maxDeg) if i%2 else randint(minDeg, max(beforeDeg-diffPrm,minDeg))
      diffDeg = courceDeg - beforeDeg
      beforeDeg = courceDeg
      courceR = int(abs(courceLength/(3.14 * (diffDeg/180))))
      f.write("_c->dS("+str(courceLength)+", "+str(courceDeg)+json_data["funcEd"])
      f.write('\n')

    f.close

def madeCourceH(json_data):
    minLengh = json_data["madePrm"]["minLengh"]
    maxLength = json_data["madePrm"]["maxLength"]
    minDeg = json_data["madePrm"]["minDeg"]
    maxDeg = json_data["madePrm"]["maxDeg"]
    diffPrm = json_data["madePrm"]["diffPrm"]
    courceR = 0
    courceLength = 0
    beforeDeg = 0

    cdir = os.path.dirname(__file__)
    file_path = cdir+"/courceH_prm.txt"
    f = open(file_path, 'w')
    # _c->dC(100,-35 + kaku);
    for i in range(20):
      courceLength = randint(minLengh, maxLength)
      courceLength2 = randint(minLengh, maxLength)
      courceDeg = randint(min(beforeDeg + diffPrm,maxDeg), maxDeg) if i%2 else randint(minDeg, max(beforeDeg-diffPrm,minDeg))
      diffDeg = courceDeg - beforeDeg
      beforeDeg = courceDeg
      courceR = int(abs(courceLength/(3.14 * (diffDeg/180))))

      f.write("_c->dS("+str(courceLength)+", "+str(courceDeg)+json_data["funcEd"])
      f.write('\n')
      f.write("_c->dS("+str(courceLength2)+", "+str(0)+json_data["funcEd"])
      f.write('\n')
    f.close

def madeCourceCH(json_data):
    minLengh = json_data["madePrm"]["minLengh"]
    maxLength = json_data["madePrm"]["maxLength"]
    minDeg = json_data["madePrm"]["minDeg"]
    maxDeg = json_data["madePrm"]["maxDeg"]
    diffPrm = json_data["madePrm"]["diffPrm"]
    courceR = 0
    courceLength = 0
    beforeDeg = 0

    cdir = os.path.dirname(__file__)
    file_path = cdir+"/courceCH_prm.txt"
    f = open(file_path, 'w')
    # _c->dC(100,-35 + kaku);
    for i in range(20):
      courceLength = randint(minLengh, maxLength)
      courceLength2 = randint(minLengh, maxLength)
      courceDeg = randint(min(beforeDeg + diffPrm,maxDeg), maxDeg) if i%2 else randint(minDeg, max(beforeDeg-diffPrm,minDeg))
      diffDeg = courceDeg - beforeDeg
      beforeDeg = courceDeg
      courceR = int(abs(courceLength/(3.14 * (diffDeg/180))))
      if(randint(0,1)==0):
        f.write("_c->dS("+str(courceLength)+", "+str(courceDeg)+json_data["funcEd"])
        f.write('\n')
        f.write("_c->dS("+str(courceLength2)+", "+str(0)+json_data["funcEd"])
        f.write('\n')
      else:
        f.write(json_data["funcSt"]+str(courceR)+", "+str(courceDeg)+json_data["funcEd"])
        f.write('\n')
    f.close

def madeCourceCK(json_data):
    minLengh = json_data["madePrm"]["minLengh"]
    maxLength = json_data["madePrm"]["maxLength"]
    minDeg = json_data["madePrm"]["minDeg"]
    maxDeg = json_data["madePrm"]["maxDeg"]
    diffPrm = json_data["madePrm"]["diffPrm"]
    courceR = 0
    courceLength = 0
    beforeDeg = 0

    cdir = os.path.dirname(__file__)
    file_path = cdir+"/courceCK_prm.txt"
    f = open(file_path, 'w')
    # _c->dC(100,-35 + kaku);
    for i in range(20):
      courceLength = randint(minLengh, maxLength)
      courceDeg = randint(min(beforeDeg + diffPrm,maxDeg), maxDeg) if i%2 else randint(minDeg, max(beforeDeg-diffPrm,minDeg))
      diffDeg = courceDeg - beforeDeg
      beforeDeg = courceDeg
      courceR = int(abs(courceLength/(3.14 * (diffDeg/180))))
      if(randint(0,1)==0):
        f.write(json_data["funcSt"]+str(courceR)+", "+str(courceDeg)+json_data["funcEd"])
      else:
        f.write("_c->dS("+str(courceLength)+", "+str(courceDeg)+json_data["funcEd"])

      f.write('\n')
    f.close

cdir = os.path.dirname(__file__)
path = cdir+'/cource_prm.json'

json_file = open(path, 'r')
json_data = json.load(json_file)

madeCourceC(json_data)
madeCourceK(json_data)
madeCourceCK(json_data)
madeCourceH(json_data)
madeCourceCH(json_data)
