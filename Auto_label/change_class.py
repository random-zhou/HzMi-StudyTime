import os

def change_class(class_path,class_name):
    label_files=[f for f in os.listdir(class_path) if f.endswith('.txt')]#标签训练集
    
    for lanel_file in label_files:
        if lanel_file=='classes.txt':
            continue
        a=0
        fp=open(os.path.join(class_path,lanel_file),mode='r',encoding='utf-8')
        a=fp.readlines()
        fp.close()
        fp=open(os.path.join(class_path,lanel_file),mode='w',encoding='utf-8')
        s=''
        for i in a:
            d=str(class_name)+i[1:]
            s=s+d
        fp.write(s)
        fp.close()
#if __name__ == '__main__':
    