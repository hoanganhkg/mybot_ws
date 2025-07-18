// Generated by gencpp from file utils/CommandIntRequest.msg
// DO NOT EDIT!


#ifndef UTILS_MESSAGE_COMMANDINTREQUEST_H
#define UTILS_MESSAGE_COMMANDINTREQUEST_H


#include <string>
#include <vector>
#include <memory>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace utils
{
template <class ContainerAllocator>
struct CommandIntRequest_
{
  typedef CommandIntRequest_<ContainerAllocator> Type;

  CommandIntRequest_()
    : broadcast(false)
    , frame(0)
    , command(0)
    , current(0)
    , autocontinue(0)
    , param1(0.0)
    , param2(0.0)
    , param3(0.0)
    , param4(0.0)
    , x(0)
    , y(0)
    , z(0.0)  {
    }
  CommandIntRequest_(const ContainerAllocator& _alloc)
    : broadcast(false)
    , frame(0)
    , command(0)
    , current(0)
    , autocontinue(0)
    , param1(0.0)
    , param2(0.0)
    , param3(0.0)
    , param4(0.0)
    , x(0)
    , y(0)
    , z(0.0)  {
  (void)_alloc;
    }



   typedef uint8_t _broadcast_type;
  _broadcast_type broadcast;

   typedef uint8_t _frame_type;
  _frame_type frame;

   typedef uint16_t _command_type;
  _command_type command;

   typedef uint8_t _current_type;
  _current_type current;

   typedef uint8_t _autocontinue_type;
  _autocontinue_type autocontinue;

   typedef float _param1_type;
  _param1_type param1;

   typedef float _param2_type;
  _param2_type param2;

   typedef float _param3_type;
  _param3_type param3;

   typedef float _param4_type;
  _param4_type param4;

   typedef int32_t _x_type;
  _x_type x;

   typedef int32_t _y_type;
  _y_type y;

   typedef float _z_type;
  _z_type z;





  typedef boost::shared_ptr< ::utils::CommandIntRequest_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::utils::CommandIntRequest_<ContainerAllocator> const> ConstPtr;

}; // struct CommandIntRequest_

typedef ::utils::CommandIntRequest_<std::allocator<void> > CommandIntRequest;

typedef boost::shared_ptr< ::utils::CommandIntRequest > CommandIntRequestPtr;
typedef boost::shared_ptr< ::utils::CommandIntRequest const> CommandIntRequestConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::utils::CommandIntRequest_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::utils::CommandIntRequest_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::utils::CommandIntRequest_<ContainerAllocator1> & lhs, const ::utils::CommandIntRequest_<ContainerAllocator2> & rhs)
{
  return lhs.broadcast == rhs.broadcast &&
    lhs.frame == rhs.frame &&
    lhs.command == rhs.command &&
    lhs.current == rhs.current &&
    lhs.autocontinue == rhs.autocontinue &&
    lhs.param1 == rhs.param1 &&
    lhs.param2 == rhs.param2 &&
    lhs.param3 == rhs.param3 &&
    lhs.param4 == rhs.param4 &&
    lhs.x == rhs.x &&
    lhs.y == rhs.y &&
    lhs.z == rhs.z;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::utils::CommandIntRequest_<ContainerAllocator1> & lhs, const ::utils::CommandIntRequest_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace utils

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsFixedSize< ::utils::CommandIntRequest_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::utils::CommandIntRequest_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::utils::CommandIntRequest_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::utils::CommandIntRequest_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::utils::CommandIntRequest_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::utils::CommandIntRequest_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::utils::CommandIntRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "6165959012c47e0f665b640c1ab12391";
  }

  static const char* value(const ::utils::CommandIntRequest_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x6165959012c47e0fULL;
  static const uint64_t static_value2 = 0x665b640c1ab12391ULL;
};

template<class ContainerAllocator>
struct DataType< ::utils::CommandIntRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "utils/CommandIntRequest";
  }

  static const char* value(const ::utils::CommandIntRequest_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::utils::CommandIntRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "# Generic COMMAND_INT\n"
"\n"
"bool broadcast # send this command in broadcast mode\n"
"\n"
"uint8 frame\n"
"uint16 command\n"
"uint8 current\n"
"uint8 autocontinue\n"
"float32 param1\n"
"float32 param2\n"
"float32 param3\n"
"float32 param4\n"
"int32 x	# latitude in deg * 1E7 or local x * 1E4 m\n"
"int32 y	# longitude in deg * 1E7 or local y * 1E4 m\n"
"float32 z	# altitude\n"
;
  }

  static const char* value(const ::utils::CommandIntRequest_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::utils::CommandIntRequest_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.broadcast);
      stream.next(m.frame);
      stream.next(m.command);
      stream.next(m.current);
      stream.next(m.autocontinue);
      stream.next(m.param1);
      stream.next(m.param2);
      stream.next(m.param3);
      stream.next(m.param4);
      stream.next(m.x);
      stream.next(m.y);
      stream.next(m.z);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct CommandIntRequest_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::utils::CommandIntRequest_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::utils::CommandIntRequest_<ContainerAllocator>& v)
  {
    s << indent << "broadcast: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.broadcast);
    s << indent << "frame: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.frame);
    s << indent << "command: ";
    Printer<uint16_t>::stream(s, indent + "  ", v.command);
    s << indent << "current: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.current);
    s << indent << "autocontinue: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.autocontinue);
    s << indent << "param1: ";
    Printer<float>::stream(s, indent + "  ", v.param1);
    s << indent << "param2: ";
    Printer<float>::stream(s, indent + "  ", v.param2);
    s << indent << "param3: ";
    Printer<float>::stream(s, indent + "  ", v.param3);
    s << indent << "param4: ";
    Printer<float>::stream(s, indent + "  ", v.param4);
    s << indent << "x: ";
    Printer<int32_t>::stream(s, indent + "  ", v.x);
    s << indent << "y: ";
    Printer<int32_t>::stream(s, indent + "  ", v.y);
    s << indent << "z: ";
    Printer<float>::stream(s, indent + "  ", v.z);
  }
};

} // namespace message_operations
} // namespace ros

#endif // UTILS_MESSAGE_COMMANDINTREQUEST_H
