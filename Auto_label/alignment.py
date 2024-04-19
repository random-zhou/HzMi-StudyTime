import os


def alignment(img_path,label_path,cl_de=False):
    image_files = [f for f in os.listdir(img_path) if f.endswith('.jpg') or f.endswith('.png')]  
    label_files = [f for f in os.listdir(label_path) if f.endswith('.txt')]
    
    for label_file in label_files:#标签多
        if label_file=='classes.txt' and not cl_de:
            continue
        l_file,_=os.path.splitext(label_file)
        img_file=l_file+'.jpg'
        if img_file not in image_files:
            os.remove(os.path.join(label_path,label_file))
            print(os.path.join(label_path,label_file),'多',"被删除")
        
    for iamge_file in image_files:#图片多
        img_file,_=os.path.splitext(iamge_file)
        l_file=img_file+'.txt'
        if l_file not in label_files:
            os.remove(os.path.join(img_path,iamge_file))
            print(os.path.join(img_path,iamge_file),'多',"被删除")
            
if __name__ == "__main__":
    img_path='data\\1712389104\\images\\train'
    label_path="data\\1712389104\\labels\\train"
    alignment(img_path,label_path,cl_de=True)

