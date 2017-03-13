#ifndef VECTOR_H
#define VECTOR_H
#include"cap.h"
#include"new.h"
#include"iterator.h"

template < typename T >
class Vector
{
public:
    //!
    //! \brief Value_type type of elements stored in the Vector
    //!
    using Value_type = T;
    using iterator   = T*;


    //!
    //! \brief Vector constructor
    //!
    Vector():
        data_    ( nullptr ),
        capacity_( 0 ),
        size_    ( 0 )
    {
    #ifdef ALL_CHECK
        cout << __PRETTY_FUNCTION__ << endl;
    #endif
    }

    //!
    //! \brief Vector constructor
    //!
    Vector( size_t capacity ):
        data_    ( new Value_type [ capacity ] ),
        capacity_( capacity ),
        size_    ( 0 )
    {
        cout << __PRETTY_FUNCTION__ << endl;
        //ASSERT_OK( this )
    }

    //!
    //! \brief Vector copy constructor
    //! \param that
    //!
    explicit Vector( const Vector& that ):
        data_    ( new Value_type [ that.capacity_ ] ),
        capacity_( that.capacity_ ),
        size_    ( that.size_)
    {
        cout << __PRETTY_FUNCTION__ << endl;
        //ASSERT_OK( that )

        std::copy( that.data_, that.data_ + that.size_, this->data_ );

        //ASSERT_OK( this )
    }

    //!
    //! \brief ~Vector destructor
    //!
    ~Vector()
    {
        delete[] data_;
        data_ = nullptr;
        capacity_ = POISON;
        size_ = POISON;
    #ifdef ALL_CHECK
        cout << __PRETTY_FUNCTION__ << endl;
    #endif
    }

    iterator begin() const
    {
        return &data_[ 0 ];
    }

    iterator end() const
    {
        return &data_[ size_ ];
    }

    //!
    //! \brief operator [] redefined operator with checking for data out-of-bounds
    //! \param index
    //! \return link on array element with index number ( if index <= capacity_ )
    //!
    Value_type& operator [] ( size_t index )
    {
        //ASSERT_OK( this )

        assert( index < capacity_ && "ERROR!!!Out of!" );
        return data_[ index ];
    }

//  it makes no sense to implement this function, as its ability to take on []
//    const Vector< T >& at( size_t indez )
//    {
//        //ASSERT( index < capacity_ && "ERROR!!!Out of!" );
//        return data_[ index ];
//    }

    //!
    //! \brief operator = redefined for working whith elements of class Vector
    //! \param that
    //! \return link on element This after assignments to That
    //!
    const Vector< T >& operator = ( const Vector< T >& that )
    {
        cout << __PRETTY_FUNCTION__ << endl;
        //ASSERT_OK( this )
        //ASSERT_OK( that )

        if( this == &that )
            return *this;

        Vector< T > victim( that );

        //ASSERT_OK( victim )

        swap( victim );

        //ASSERT_OK( this )

        return *this;
    }

//    const Vector< T >& operator = ( Value_type value )
//    {
//        cout << __PRETTY_FUNCTION__ << endl;
//        //ASSERT_OK( this )

//        data
//    }

    //!
    //! \brief empty checks if the container has no elements, i.e. whether begin() == end()
    //! \return true if the container is empty, false otherwise
    //!
    bool empty() const
    {
        cout << __PRETTY_FUNCTION__ << endl;
        //ASSERT_OK( this )

        return !size_;
    }

    //!
    //! \brief size returns the number of elements in the container
    //! \return the number of elements in the container
    //!
    size_t size() const
    {
        cout << __PRETTY_FUNCTION__ << endl;

        //ASSERT_OK( this )

        return size_;
    }

    //!
    //! \brief capacity returns the number of elements that the container has currently allocated space for
    //! \return capacity of the currently allocated storage
    //!
    size_t capacity() const
    {
        cout << __PRETTY_FUNCTION__ << endl;

        //ASSERT_OK( this )

        return capacity_;
    }

    //!
    //! \brief reserve increase the capacity of the container to a value that's equal to new_cap
    //! \param new_size new capacity of the containe
    //!
    void reserve( size_t new_cap )
    {
        cout << __PRETTY_FUNCTION__ << endl;

        //ASSERT_OK( this )

        if( new_cap <= capacity_ )
            cout << " ERROR!!!Resizing is not possible, data loss is expected!!!" << endl;
            return;

        Value_type* new_data = new Value_type [ new_cap ];
        for( int i = 0; i < capacity_; ++i )
            new_data[ i ] = data_ [ i ];

        delete[] data_;
        data_ = new_data;
        capacity_ = new_cap;

        //ASSERT_OK( this )

    }

    //!
    //! \brief shrink_to_fit requests the removal of unused capacity.
    //!
    void shrink_to_fit()
    {

        cout << __PRETTY_FUNCTION__ << endl;

        //ASSERT_OK( this )

        if( size_ == capacity_)
        {

            //ASSERT_OK( this )

            return;
        }

        Value_type* new_data = new Value_type [ size_ ];
        for( int i = 0; i < size_; ++i )
            new_data[ i ] = data_ [ i ];

        delete[] data_;
        data_ = new_data;
        capacity_ = size_;

        //ASSERT_OK( this )

    }

    //!
    //! \brief clear removes all elements from the container.
    //!
    void clear()
    {
        cout << __PRETTY_FUNCTION__ << endl;

        //ASSERT_OK( this )

        for( int i = 0; i < size_; ++i )
            data_[ i ] = POISON;
        size_ = 0;

        //ASSERT_OK( this )
    }

    //!
    //! \brief pop_back removes the last element of the container
    //!
    void pop_back()
    {
        cout << __PRETTY_FUNCTION__ << endl;

        //ASSERT_OK( this )

        if( !this->empty() )
            data_[ size_-- ] = POISON;
        else
            cout << "Stack is empty!" << endl;

        //ASSERT_OK( this )
    }

    //!
    //! \brief push_back appends the given element value to the end of the container
    //! \param value the value of the element to append
    //!
    void push_back( const Value_type& value )
    {

        cout << __PRETTY_FUNCTION__ << endl;

        //ASSERT_OK( this )

        double_capacity();//????
        data_[ size_++ ] = value;

        //ASSERT_OK( this )
    }

    //!
    //! \brief operator << overloaded output statement for a vector
    //! \param os
    //! \param OutVector output vector
    //! \return
    //!
    friend ostream& operator << ( ostream& os, const Vector& OutVector )
    {
        cout << __PRETTY_FUNCTION__ << endl;

        for( Iterator< Value_type > it = OutVector.begin(); it != OutVector.end(); ++it )
            os << *it << " ";

        os << endl;

        os << "Size: " << OutVector.size_ << " Capacity: " << OutVector.capacity_;

        return os;
    }

    //!
    //! \brief Dump prints on screen information about elements
    //!
    void Dump() const
    {
        cout << "\n"            << __PRETTY_FUNCTION__            << endl;

        cout << "\nVector: "    << ( Ok() ? "Correct" : "Incorrect" ) << endl;

        cout << "\nCapacity: "  << capacity_                      << endl;
        cout << "Size: "        << size_                          << endl;

        for( size_t i = 0; i < capacity_; ++i )
        {
            cout << ( i < size_ ? "* " : "  " );
            cout << "[ " << i << " ] = " << data_[ i ];
            cout << " adress: " << &data_[ i ] << endl;
        }
        getch();
    }

    //!
    //! \brief swap
    //! \param that
    //!
    void swap( Vector< T > &that )
    {
        std::swap( this->data_,     that.data_ );
        std::swap( this->capacity_, that.capacity_ );
        std::swap( this->size_,     that.size_ );

        cout << "\n" << __PRETTY_FUNCTION__ << endl;
    }

private:

    Value_type* data_;

    size_t capacity_;

    size_t size_;

    //!
    //! \brief Ok verifies the vector
    //! \return TRUE if vector is correct, FALSE otherwise
    //!
    bool Ok() const
    {
        return size_ <= capacity_;
    }

    //!
    //! \brief double_capacity increases the memory used by the vector in two
    //!
    void double_capacity()
    {
       if( size_ == capacity_ )
           reserve( capacity_ > 0 ? 2*capacity_ : 1 );
    }

};

#endif // VECTOR_H
