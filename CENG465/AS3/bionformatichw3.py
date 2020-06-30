import math
from Bio.PDB import *
from Bio.PDB.PDBParser import PDBParser

#To get only the Atom records
orjinalfiles = ["2bti.pdb","3r0a.pdb","4uap.pdb","6k62.pdb","6k97.pdb","6lac.pdb"]
modifiedfiles = ["2btimodify.pdb","3r0amodify.pdb","4uapmodify.pdb","6k62modify.pdb","6k97modify.pdb","6lacmodify.pdb"]
#Write a new file only from the ATOM record of the pdb file
def modifyFile(orj,modif):
    f = open(modif,"w")
    for line in open(orj):
        list = line.split()
        id = list[0]
        if id == 'ATOM':
            f.write(line)

def modifyAll():
    for i in range(6):
        modifyFile(orjinalfiles[i],modifiedfiles[i])
#####################################################for files done only for once #######################


#Take two protein coordinate from different chain returns the Euclidean distance
def eucDistance(coordA, coordB):
    distance = math.sqrt(sum([(a - b) ** 2 for a, b in zip(coordA, coordB)]))
    return distance


#Get coordinates of the chain and its residue name and order at the end of the list as another list
def getCoordinates(chainId,structure):
    result = []
    pair = []
    pairs = []
    for model in structure.get_list():
        for chain in model.get_list():
            if(chain.get_id() == chainId):
                for residue in chain.get_list():
                    if residue.has_id("CB") :
                        full_id = residue.get_id()
                        seqNum = full_id[1]
                        resName = residue.get_resname()
                        ca = residue["CB"]

                    else: # For Glycine
                        if(residue.has_id("CA")):
                            full_id = residue.get_id()
                            seqNum = full_id[1]
                            resName = residue.get_resname()
                            ca = residue["CA"]

                    pair.append(resName)
                    pair.append(seqNum)
                    pairs.append(pair)
                    pair = []
                    a = ca.get_coord()
                    result.append(a)

    result.append(pairs)
    return result


def calculateEucDistAndPair(chainA,chainB):
    count1 = 0

    pair = []
    pairs = []

    paircoord = []
    pairscoord = []

    lenChainA = len(chainA)-1
    lenChainB = len(chainB)-1
    for i in range(lenChainA):
        for j in range(lenChainB):
            d = eucDistance(chainA[i],chainB[j])
            if(d<8):
                #print chainA[lenChainA][i], chainB[lenChainB][j]

                paircoord.append(chainA[i])
                paircoord.append(chainB[j])
                pairscoord.append(paircoord)
                paircoord = []

                pair.append(chainA[lenChainA][i])
                pair.append(chainB[lenChainB][j])
                pairs.append(pair)
                pair = []
                count1+=1

    print "There are "+str(count1) +" interacting pairs."
    pairscoord.append(pairs)

    return pairscoord


def closestDistanceBetwPairsLessThan8(Pair1,Pair2):
    for i in range(2):
        for j in range(2):
            dis = eucDistance(Pair1[i],Pair2[j])
            if(dis<8):
                return True
    return False


############################what is there is more than 1 group
def groupPairs(Pairs):
    lenPairs = len(Pairs)
    group = []
    groups = []
    count = 0

    for i in range(lenPairs-1):
        for j in range(lenPairs-1):
            if(closestDistanceBetwPairsLessThan8(Pairs[i],Pairs[j]) and i != j): #distance between the same index is 0 don't add it
                group.append(Pairs[lenPairs-1][i])
                count +=1
                break
            else:
                if(j==lenPairs-2 ):
                    if(group != []):
                        groups.append(group)
                    group = []
                    group.append(Pairs[lenPairs-1][i])
                    break	

    
    if(group != []):
       groups.append(group)

    return groups
############################

def printAccordingly(G):
    lenG = len(G)
    for i in range(1,lenG+1):
        s = len(G[i-1])
        for j in range(s):
            print "Group "+str(i) +": "+ G[i-1][j][0][0] +"("+ str(G[i-1][j][0][1]) + ")"+ "-"+ G[i-1][j][1][0] +"("+ str(G[i-1][j][1][1]) + ")"
    print "Number of groups =",lenG
    print "\n"



def main():
    a = 0
    for i in modifiedfiles:
        print orjinalfiles[a]
        a+=1
        p = PDBParser()
        structure = p.get_structure('X', i)
        ACoordList = getCoordinates("A",structure)
        BCoordList = getCoordinates("B",structure)
        P = calculateEucDistAndPair(ACoordList,BCoordList)
        g = groupPairs(P)
        printAccordingly(g)




def run():
    modifyAll()
    main()

run()



