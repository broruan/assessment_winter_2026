from torch import nn

# 搭建神经网络

class Model(nn.Module):
    def __init__(self):
        super(Model,self).__init__()
        self.model = nn.Sequential(
            nn.Conv2d(in_channels=1,out_channels=6,kernel_size=5,stride=1,padding=0),
            nn.MaxPool2d(2),
            nn.Conv2d(in_channels=6,out_channels=16,kernel_size=3,stride=3,padding=8),
            nn.MaxPool2d(2),
            nn.Flatten(),
            nn.Linear(256,120),
            nn.Linear(120,84),
            nn.Linear(84,10)
        )

    def forward(self,x):
        return self.model(x)
