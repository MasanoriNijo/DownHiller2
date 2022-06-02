from asyncore import write
import json
import os

def madeHeaderFile(json_data):
  cdir = os.path.dirname(__file__)
  file_path = cdir+"/"+json_data["className"]+".h"
  f = open(file_path, 'w')
  f.write('#include "cocos2d.h"\n')
  f.write('USING_NS_CC;\n')
  f.write('\n')
  if json_data["superClass"] == '':
    f.write('class '+json_data['className']+' {\n')
  else:
    f.write('class '+json_data['className']+':'+json_data["superClass"]+' {\n')

  f.write('protected:\n')
  f.write('  '+json_data['className']+'();\n')
  f.write('  '+'virtual ~'+json_data['className']+'();\n')
  f.write('  '+'bool init() override;\n')
  f.write('\n')
  f.write('public:\n')
  f.write('  '+'CREATE_FUNC('+json_data['className']+');\n')
  f.write('  '+'static Scene* createScene();\n')

  for prms in json_data['synthesize_retains']:
    f.write('  CC_SYNTHESIZE_RETAIN(')
    f.write(prms[0]+'*,')
    f.write(prms[1]+',')
    f.write(prms[2]+');\n')

  f.write('  void update(float dt) override;\n')
  f.write('  void onEnterTransitionDidFinish() override;\n')
  f.write('};\n')
  f.close


def madeCCPFile(json_data):
  cdir = os.path.dirname(__file__)
  file_path = cdir+"/"+json_data["className"]+".cpp"
  f = open(file_path, 'w')
  f.write('#include "'+json_data['className']+'.h"\n\n')
  f.write(json_data['className']+'::'+json_data['className']+'():\n')

  secondFlg=False
  for prms in json_data['synthesize_retains']:
    if secondFlg:
      f.write(', '+prms[1]+'(NULL)')
    else:
      secondFlg = True
      f.write(prms[1]+'(NULL)')
  f.write('\n{}\n\n')

  f.write(json_data['className']+'::~'+json_data['className']+'() {\n')
  for prms in json_data['synthesize_retains']:
      f.write('	CC_SAFE_RELEASE_NULL('+prms[1]+');\n')
  f.write('}\n\n')

  f.write('Scene* '+json_data['className']+'::createScene() {\n')
  f.write('  auto scene = Scene::create();\n')
  f.write('  auto layer = '+json_data['className']+'::create();\n')
  f.write('    scene->addChild(layer);\n')
  f.write('  return scene;\n')
  f.write('}\n\n')

  f.write('bool '+json_data['className']+'::init() {\n')
  f.write('  // todo\n')
  f.write('  return true;\n')
  f.write('}\n\n')

  f.write('void '+json_data['className']+'::onEnterTransitionDidFinish() {\n')
  f.write('  // todo\n')
  f.write('}\n\n')

  f.write('void '+json_data['className']+'::update(float dt) {\n')
  f.write('  // todo\n')
  f.write('}\n\n')

  f.write('/** パラメータサンプル\n')
  for prms in json_data['synthesize_retains']:
    f.write('this->set'+prms[2]+'('+prms[0]+'::create());\n')
    f.write('this->get'+prms[2]+'();\n')


  f.write('*/')
  f.close

cdir = os.path.dirname(__file__)
path = cdir+'/cocos_file_prm.json'

json_file = open(path, 'r')
json_data = json.load(json_file)

madeHeaderFile(json_data)
madeCCPFile(json_data)

