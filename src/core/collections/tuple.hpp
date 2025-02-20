#ifndef ST_TUPLE_H
#define ST_TUPLE_H

namespace starry {

/// tuple
template<typename T1, typename T2>
class Tuple2 {
public:
    T1 item1;
    T2 item2;

    Tuple2(T1 item1, T2 item2)
    {
        this->item1 = item1;
        this->item2 = item2;
    }
};

}

#endif // ST_TUPLE_H
