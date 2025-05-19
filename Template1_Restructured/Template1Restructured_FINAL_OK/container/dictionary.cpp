
namespace lasd {

/* ************************************************************************** */

// Specific member functions (DictionaryContainer)

template<typename Data>
inline bool DictionaryContainer<Data>::InsertAll(const TraversableContainer<Data>& container) {
    bool flag = true;
    container.Traverse(
        [this, &flag](const Data& data) {
            flag = flag && Insert(data);
        }
    );
    return flag;
}

template<typename Data>
inline bool DictionaryContainer<Data>::InsertAll(MappableContainer<Data>&& container) {
    bool flag = true;
    container.Map(
        [this, &flag](Data& data) {
            flag = flag && Insert(std::move(data));
        }
    );
    return flag;
}

template<typename Data>
inline bool DictionaryContainer<Data>::RemoveAll(const TraversableContainer<Data>& container) {
    bool flag = true;
    container.Traverse(
        [this, &flag](const Data& data) {
            flag = flag && Remove(data);
        }
    );
    return flag;
}

template<typename Data>
inline bool DictionaryContainer<Data>::InsertSome(const TraversableContainer<Data>& container) {
    bool flag = false;
    container.Traverse(
        [this, &flag](const Data& data) {
            flag = flag || Insert(data);
        }
    );
    return flag;
}

template<typename Data>
inline bool DictionaryContainer<Data>::InsertSome(MappableContainer<Data>&& container) {
    bool flag = false;
    container.Map(
        [this, &flag](Data& data) {
            flag = flag || Insert(std::move(data));
        }
    );
    return flag;
}

template<typename Data>
inline bool DictionaryContainer<Data>::RemoveSome(const TraversableContainer<Data>& container) {
    bool flag = false;
    container.Traverse(
        [this, &flag](const Data& data) {
            flag = flag || Remove(data);
        }
    );
    return flag;
}
    
/* ************************************************************************** */
    
}
    