import os.path
import sys
crt_dir = os.path.dirname(os.path.abspath(__file__))
#sys.path.insert(0,os.path.join(crt_dir, '..'))
_data_dir = os.path.join(crt_dir, '..', 'data')
car_csv = os.path.join(_data_dir, 'car.csv')
iris_train = os.path.join(_data_dir, 'iris.train')
iris_csv = os.path.join(_data_dir, 'iris.csv')
birds_txt = os.path.join(_data_dir, 'birds_txt.dat')
heterodata_train = os.path.join(_data_dir, 'heterodata.train')
