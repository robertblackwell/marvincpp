#ifndef m_buffer_hpp
#define m_buffer_hpp
#include <stddef.h>
#include <memory>
#include <iostream>
#include <iterator>
#include <boost/asio/buffer.hpp>

namespace Marvin {

class MBuffer;
using MBufferSPtr =  std::shared_ptr<MBuffer>;
using MBufferUPtr =  std::unique_ptr<MBuffer>;

#pragma mark - MBuffer class

/**
*
* \ingroup buffers
* \brief MBuffer provides a contiguous expanding buffer
*
* MBuffer class wraps a contigous buffer and provides manipulation methods.
* Once constructed the Mbuffer instance "own" the raw memory.
* MBuffer destructor releases the raw memory.
*/
class MBuffer {
public:
    static std::size_t min_buffer_size;
    static MBufferSPtr makeSPtr(std::size_t capacity);
    static MBufferSPtr makeSPtr(std::string s);
    static MBufferSPtr makeSPtr(void* mem, std::size_t size);
    static MBufferSPtr makeSPtr(MBuffer& mb);

    /**
     * Constructor - give it a slab of memory to manage
     * Let the MBuffer constructor allocate the memory - but tell it howmuch
     */
    MBuffer(const std::size_t cap);
    MBuffer(std::string str);
    MBuffer(MBuffer& other);
    MBuffer& operator =(MBuffer& other);
    MBuffer(MBuffer&& other);
    MBuffer& operator =(MBuffer&& other);
    
    /**
     * destrtuctor - frees the memory the instance is managing
     */
    ~MBuffer();
    
    /**
     * gets a pointer to the start of the memory slab being managed by the instance
     */
    void* data();
    
    /**
     * gets the size of used portion of the buffer
    */
     std::size_t size();
    
    /**
     * capacity of the buffer - max value of size
    */
    std::size_t capacity();
    
    /**
     * returns a pointer to the next available unused position in the buffer
    */
    void* nextAvailable();
    
    /**
     * Resets the buffer so that it is again an empty buffer
     */
    MBuffer& empty();
    
    /** adds (by copying) data to the buffer starting at the first unsed byte*/
    MBuffer& append(void* data, std::size_t len);
    /**
     * convenience overloads
     */
    MBuffer& append(std::string* str);
    /**
     * for constants and variables
     */
    MBuffer& append(std::string const& str);
    /**
     * for literals
     */
    MBuffer& append(std::string&& str);

    MBuffer& setSize(std::size_t n);
    
    /**
     * Returns a string that has the same value as the used portion of the buffer
     */
    std::string toString();
    
    /**
     * Detremines if an address value (pointer) is within the address range of the
     * the buffer ie
     *      buffer.dada() < = ptr < buffer.data() + buffer.capacity();
     *  or, should it be
     *      buffer.dada() < = ptr < buffer.data() + buffer.size();
     *
     */
    bool contains(void* ptr);
    bool contains(char* ptr);
    
    /**
     * converts an MBuffer to a boost::asio::const_buffer
     */
    friend boost::asio::const_buffer mb_as_const_buffer(MBuffer& bm);

    /**
     * converts an MBuffer to a boost::asio::mutable_buffer
     */
    friend boost::asio::mutable_buffer mb_as_mutable_buffer(MBuffer& bm);
//    friend boost::asio::const_buffer_1 mb_as_asio_const_buffer(MBuffer& mb);

    friend std::ostream &operator<< (std::ostream &os, MBuffer &b);

protected:
    
    void*       m_memPtr;     /// points to the start of the memory slab managed by the instance
    char*       m_cPtr;       /// same as memPtr but makes it easier in debugger to see whats in the buffer
    std::size_t m_length;    ///
    std::size_t m_capacity;  /// the capacity of the buffer, the value used for the malloc call
    std::size_t m_size;      /// size of the currently filled portion of the memory slab
};

} //namespace Marvin
#endif
