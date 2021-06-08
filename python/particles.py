from particle import Particle

class Particles:
    def __init__(self,n):
        for i in range(n):
            setattr(self,'p%i'i,Particle())

    def __getiem__(self,key):
        return self.__getattribute__(key)

    def __getattribute__(self,key):
        try:
            return self.__dict__['p%i'%key]
        except KeyError:
            return 'default'