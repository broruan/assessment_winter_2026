import os
os.environ["KMP_DUPLICATE_LIB_OK"]="TRUE"

import torch
import torchvision
from torch.utils.data import DataLoader
from model import Model


data_train = torchvision.datasets.MNIST("./Datasets/train",train=True,transform=torchvision.transforms.ToTensor(),download=True)
data_val = torchvision.datasets.MNIST("./Datasets/val",train=False, transform=torchvision.transforms.ToTensor(), download=True)

train_loader = DataLoader(data_train,batch_size=2,shuffle=True,drop_last=True)
val_loader = DataLoader(data_val,batch_size=2,shuffle=True,drop_last= True)

# 损失函数
loss = torch.nn.CrossEntropyLoss()

# 优化器
train = Model()
learning_rate = 0.01
optim = torch.optim.SGD(train.parameters(),lr=learning_rate)

epoch = 10



for i in range(epoch):
    print(f"***********第{i}次训练开始*************")
    for i,data in enumerate(train_loader):
        imgs,target = data
        output = train(imgs)

        # 计算损失
        l = loss(output,target)
        print(f"损失为：{l}")
        # 梯度归零
        optim.zero_grad()
        l.backward()
        optim.step()


    # 验证测试集

    with torch.no_grad():
        total_correct = 0
        for i,data in enumerate(val_loader):
            imgs,target = data
            output = train(imgs)
            l2 =loss(output,target)
            total_correct += l2.item()
            
        print(f"测试集上的损失为：{total_correct}")

torch.save(train.state_dict(),"./model.pth")