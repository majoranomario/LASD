
namespace lasd {

/* ************************************************************************** */

// Specific member functions (TraversableContainer)

template<typename Data>
template<typename Accumulator>
inline Accumulator TraversableContainer<Data>::Fold(FoldFun<Accumulator> function,Accumulator accumulator) const {
    Traverse(
      [function, &accumulator](const Data & data){
        accumulator = function(data,accumulator);
      }
    );
    return accumulator;
}

template<typename Data>
inline bool TraversableContainer<Data>::Exists(const Data & value) const noexcept {
  bool flag = false;
  Traverse(
    [value, &flag](const Data & data){
      if(!flag){
        if(data == value){
          flag = true;
        }
      }
    }
  );
  return flag;
}

/* ************************************************************************** */

// Specific member functions (PreOrderTraversableContainer)

template<typename Data>
template<typename Accumulator>
inline Accumulator PreOrderTraversableContainer<Data>::PreOrderFold(FoldFun<Accumulator> function, Accumulator accumulator) const {
  PreOrderTraverse(
    [function, &accumulator](const Data & data) {
      accumulator = function(data, accumulator);
    }
  );
  return accumulator;
}

template<typename Data>
inline void PreOrderTraversableContainer<Data>::Traverse(TraverseFun function) const {
  PreOrderTraverse(function);
}

/* ************************************************************************** */

// Specific member functions (PostOrderTraversableContainer)

template <typename Data>
template <typename Accumulator>
inline Accumulator PostOrderTraversableContainer<Data>::PostOrderFold(FoldFun<Accumulator> function, Accumulator accumulator) const {
  PostOrderTraverse(
    [function, &accumulator](const Data & data) {
      accumulator = function(data, accumulator);
    }
  );
  return accumulator;
}

template <typename Data>
inline void PostOrderTraversableContainer<Data>::Traverse(TraverseFun function) const {
  PostOrderTraverse(function);
}

/* ************************************************************************** */

}
