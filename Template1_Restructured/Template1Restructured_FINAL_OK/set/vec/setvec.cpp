
namespace lasd {

/* ************************************************************************** */

// Default constructor
template<typename Data>
SetVec<Data>::SetVec() : size(2), head(0),capacity(0){}

/* ************************************************************************ */

// Specific constructors

template<typename Data>
SetVec<Data>::SetVec(ulong newSize) : Vector(newSize) , head(0), tail(0) {}

template<typename Data>
SetVec<Data>::SetVec(const TraversableContainer<Data> & container) : SetVec(container.Size()) {
    SetVec(container.Size());
    container.Traverse(
        [this](const Data & data){
            this->Insert(data);
        }
    );
}

template<typename Data>
SetVec<Data>::SetVec(MappableContainer<Data> && container) : SetVec(container.Size()) {
    container.Map(
        [this](Data & data) {
            this->Insert(std::move(data));
        }
    );
}

/* ************************************************************************ */

// Copy constructor

template<typename Data>
SetVec<Data>::SetVec(const SetVec<Data>& setVector) {
    Vector<Data>::Vector(setVector);
}


//Move costructor

template<typename Data>
SetVec<Data>::SetVec(SetVec<Data> && setVec){
    Vector<Data>::Vector(setVector);
}



/* ************************************************************************** */

}
