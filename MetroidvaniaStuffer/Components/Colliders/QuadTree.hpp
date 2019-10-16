//
//  QuadTree.hpp
//  MetroidvaniaStuffer
//
//  Created by Victor Navarro on 10/14/19.
//  Copyright © 2019 Victor Navarro. All rights reserved.
//

#ifndef QuadTree_hpp
#define QuadTree_hpp

#include <memory>
#include <vector>

#include "CBoxCollider.hpp"
#include "Object.hpp"

class QuadTree
{
public:
    QuadTree();
    QuadTree(int maxObjects, int maxLevels, int level, sf::FloatRect bounds, QuadTree* parent);
    
    //Insert objects into the Quadtree
    void insert(std::shared_ptr<CBoxCollider> object);
    
    //Removes object from our quadtree when no longer need it to collide
    void remove(std::shared_ptr<CBoxCollider> object);
    
    //Removes all
    void clear();
    
    // Returns vector of colliders that intersect with the search area.
    std::vector<std::shared_ptr<CBoxCollider>> search(const sf::FloatRect& area);
    
    // Returns the bounds of this node.
    const sf::FloatRect& getBounds() const;
    
private:
    void search(const sf::FloatRect& area, std::vector<std::shared_ptr<CBoxCollider>>& overlappingObjects);
    
    // Returns the index for the node that will contain
    // the object. -1 is returned if it is this node
    int getChildIndexForObjects(const sf::FloatRect& objectBounds);
    
    //Creates child nodes
    void split();
    
    //Indices for the children;
    static const int thisThree = -1;
    static const int childNE = 0;
    static const int childNW = 1;
    static const int childSW = 2;
    static const int childSE = 3;
    
    int maxObjects;
    int maxLevels;
    
    // nulptr is this is the base node.
    QuadTree* parent;
    std::shared_ptr<QuadTree> children[4];
    
    // Stores objects in this node.
    std::vector<std::shared_ptr<CBoxCollider>> objects;
    
    
    // How deep the current node is from the base node.
    // The first node starts at 0 and then its child node
    // is at level 1 and so on.
    int level;
    
    // The bounds of this node.
    sf::FloatRect bounds;
};

#endif /* QuadTree_hpp */
