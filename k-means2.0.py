# clustering.py contains classes and functions that cluster data points
import sys, math, random
vectorNum = 120
# -- The Point class represents points in n-dimensional space
class Point:
    # Instance variables
    # self.coords is a list of coordinates for this Point
    # self.n is the number of dimensions this Point lives in (ie, its space)
    # self.reference is an object bound to this Point
    # Initialize new Points
    def __init__(self, coords, reference=None):
        self.coords = coords
        self.n = len(coords)
        self.reference = reference
    # Return a string representation of this Point
    def __repr__(self):
        return str(self.coords)
# -- The Cluster class represents clusters of points in n-dimensional space
class Cluster:
    # Instance variables
    # self.points is a list of Points associated with this Cluster
    # self.n is the number of dimensions this Cluster's Points live in
    # self.centroid is the sample mean Point of this Cluster
    def __init__(self, points):
        # We forbid empty Clusters (they don't make mathematical sense!)
        if len(points) == 0: raise Exception("ILLEGAL: EMPTY CLUSTER")
        self.points = points
        self.n = points[0].n
        # We also forbid Clusters containing Points in different spaces
        # Ie, no Clusters with 2D Points and 3D Points
        for p in points:
            if p.n != self.n: raise Exception("ILLEGAL: MULTISPACE CLUSTER")
        # Figure out what the centroid of this Cluster should be
        self.centroid = self.calculateCentroid()
    # Return a string representation of this Cluster
    def __repr__(self):
        return str(self.points)
    # Update function for the K-means algorithm
    # Assigns a new list of Points to this Cluster, returns centroid difference
    def update(self, points):
        old_centroid = self.centroid
        self.points = points
        self.centroid = self.calculateCentroid()
        return getDistance(old_centroid, self.centroid)
    # Calculates the centroid Point - the centroid is the sample mean Point
    # (in plain English, the average of all the Points in the Cluster)
    def calculateCentroid(self):
        centroid_coords = []
        # For each coordinate:
        for i in range(self.n):
            # Take the average across all Points
            centroid_coords.append(0.0)
            for p in self.points:
                centroid_coords[i] = centroid_coords[i]+p.coords[i]
            centroid_coords[i] = centroid_coords[i]/len(self.points)
        # Return a Point object using the average coordinates
        return Point(centroid_coords)
# -- Return Clusters of Points formed by K-means clustering
def kmeans(points, k, cutoff):
    # Randomly sample k Points from the points list, build Clusters around them
    initial = random.sample(points, k)
    clusters = []
    for p in initial: clusters.append(Cluster([p]))
    # Enter the program loop
    num = 0
    while True:
	num = num+1
	print num
        # Make a list for each Cluster
        lists = []
        for c in clusters: lists.append([])
        # For each Point:
        for p in points:
            # Figure out which Cluster's centroid is the nearest
            smallest_distance = getDistance(p, clusters[0].centroid)
            index = 0
            for i in range(len(clusters[1:])):
                distance = getDistance(p, clusters[i+1].centroid)
                if distance < smallest_distance:
                    smallest_distance = distance
                    index = i+1
            # Add this Point to that Cluster's corresponding list
            lists[index].append(p)
        # Update each Cluster with the corresponding list
        # Record the biggest centroid shift for any Cluster
        biggest_shift = 0.0
        for i in range(len(clusters)):
            shift = clusters[i].update(lists[i])
            biggest_shift = max(biggest_shift, shift)
        # If the biggest centroid shift is less than the cutoff, stop
        if biggest_shift < cutoff: break
    # Return the list of Clusters
    return clusters


# -- Get the Euclidean distance between two Points
# -- parameter k specify the dimension numbers of vector involved in calculation
def getDistance(a, b, k = vectorNum):
    # Forbid measurements between Points in different spaces
    if a.n != b.n: raise Exception("ILLEGAL: NON-COMPARABLE POINTS")
    # Euclidean distance between a and b is sqrt(sum((a[i]-b[i])^2) for all i)
    ret = 0.0
    global likeNorm
    for i in range( k ):
        ret = ret+pow((a.coords[i]-b.coords[i]), 2)
    return math.sqrt(ret)

# splitToken specify the Token to split a line into a point
def readPoint(filename ):
    infile = open(filename,'r')
    flist=[];	
    for item in infile:
	tlist = item[:-1].split(',')
	numlist = [] 
	for item in tlist:
	    numlist.append(float(item))

    	flist.append(Point(numlist));
    return flist;

# -- control the process of reading data from files. 
def readData():
    point_in = readPoint("./result.txt")
    return point_in;
# -- find the max vector
    
# -- n is the number of samples 

def getCenter(cluster):
    centerFile = open("center.txt",'w')
    for c in cluster:
        center = c.centroid
        coords = center.coords
        result=[]
        for item in coords:
            result.append(str(item))
        centerFile.write(','.join(result)+'\n')
    centerFile.close()
           
 
# -- Main function
def main(args):
    num_points, k, cutoff, lower, upper = 10, 20, 0.05, -200, 200
    # Create num_points random Points in n-dimensional space
    points = []
    # //for i in range(num_points): points.append(makeRandomPoint(n, lower, upper))
    points = readData();

    # Cluster the points using the K-means algorithm
    clusters = kmeans(points, k, cutoff)
    # Print the results

    print "\nPOINTS:"
    print len(points);
    # //for p in points: print "P:", p
    print "\nCLUSTERS:"
    print len(clusters);
    for c in clusters: print "C:", len(c.points)
    getCenter(clusters)

# -- The following code executes upon command-line invocation
if __name__ == "__main__": main(sys.argv)
