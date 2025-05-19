
namespace lasd {

/* ************************************************************************** */

// Specific member function (PreOrderMappableContainer)

template<typename Data>
inline void PreOrderMappableContainer<Data>::Map(MapFun function){
    PreOrderMap(function);
}

/* ************************************************************************** */

// Specific member function (PostOrderMappableContainer)

template<typename Data>
inline void PostOrderMappableContainer<Data>::Map(MapFun function){
    PostOrderMap(function);
}

/* ************************************************************************** */



}
