"""autogenerated by genmsg_py from telo_stateRequest.msg. Do not edit."""
import roslib.message
import struct


class telo_stateRequest(roslib.message.Message):
  _md5sum = "64e58419496c7248b4ef25731f88b8c3"
  _type = "zagrosControl/telo_stateRequest"
  _has_header = False #flag to mark the presence of a Header object
  _full_text = """string value

"""
  __slots__ = ['value']
  _slot_types = ['string']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.
    
    The available fields are:
       value
    
    @param args: complete set of field values, in .msg order
    @param kwds: use keyword arguments corresponding to message field names
    to set specific fields. 
    """
    if args or kwds:
      super(telo_stateRequest, self).__init__(*args, **kwds)
      #message fields cannot be None, assign default values for those that are
      if self.value is None:
        self.value = ''
    else:
      self.value = ''

  def _get_types(self):
    """
    internal API method
    """
    return self._slot_types

  def serialize(self, buff):
    """
    serialize message into buffer
    @param buff: buffer
    @type  buff: StringIO
    """
    try:
      _x = self.value
      length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
    except struct.error as se: self._check_types(se)
    except TypeError as te: self._check_types(te)

  def deserialize(self, str):
    """
    unpack serialized message in str into this message instance
    @param str: byte array of serialized message
    @type  str: str
    """
    try:
      end = 0
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      self.value = str[start:end]
      return self
    except struct.error as e:
      raise roslib.message.DeserializationError(e) #most likely buffer underfill


  def serialize_numpy(self, buff, numpy):
    """
    serialize message with numpy array types into buffer
    @param buff: buffer
    @type  buff: StringIO
    @param numpy: numpy python module
    @type  numpy module
    """
    try:
      _x = self.value
      length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
    except struct.error as se: self._check_types(se)
    except TypeError as te: self._check_types(te)

  def deserialize_numpy(self, str, numpy):
    """
    unpack serialized message in str into this message instance using numpy for array types
    @param str: byte array of serialized message
    @type  str: str
    @param numpy: numpy python module
    @type  numpy: module
    """
    try:
      end = 0
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      self.value = str[start:end]
      return self
    except struct.error as e:
      raise roslib.message.DeserializationError(e) #most likely buffer underfill

_struct_I = roslib.message.struct_I
"""autogenerated by genmsg_py from telo_stateResponse.msg. Do not edit."""
import roslib.message
import struct


class telo_stateResponse(roslib.message.Message):
  _md5sum = "b19c6fe489b2b2906e73c9577a122021"
  _type = "zagrosControl/telo_stateResponse"
  _has_header = False #flag to mark the presence of a Header object
  _full_text = """string remote_username
float32 battery_capacity
string power_state
bool battery_low
string tell_remote_user
string phone_home


"""
  __slots__ = ['remote_username','battery_capacity','power_state','battery_low','tell_remote_user','phone_home']
  _slot_types = ['string','float32','string','bool','string','string']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.
    
    The available fields are:
       remote_username,battery_capacity,power_state,battery_low,tell_remote_user,phone_home
    
    @param args: complete set of field values, in .msg order
    @param kwds: use keyword arguments corresponding to message field names
    to set specific fields. 
    """
    if args or kwds:
      super(telo_stateResponse, self).__init__(*args, **kwds)
      #message fields cannot be None, assign default values for those that are
      if self.remote_username is None:
        self.remote_username = ''
      if self.battery_capacity is None:
        self.battery_capacity = 0.
      if self.power_state is None:
        self.power_state = ''
      if self.battery_low is None:
        self.battery_low = False
      if self.tell_remote_user is None:
        self.tell_remote_user = ''
      if self.phone_home is None:
        self.phone_home = ''
    else:
      self.remote_username = ''
      self.battery_capacity = 0.
      self.power_state = ''
      self.battery_low = False
      self.tell_remote_user = ''
      self.phone_home = ''

  def _get_types(self):
    """
    internal API method
    """
    return self._slot_types

  def serialize(self, buff):
    """
    serialize message into buffer
    @param buff: buffer
    @type  buff: StringIO
    """
    try:
      _x = self.remote_username
      length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
      buff.write(_struct_f.pack(self.battery_capacity))
      _x = self.power_state
      length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
      buff.write(_struct_B.pack(self.battery_low))
      _x = self.tell_remote_user
      length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
      _x = self.phone_home
      length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
    except struct.error as se: self._check_types(se)
    except TypeError as te: self._check_types(te)

  def deserialize(self, str):
    """
    unpack serialized message in str into this message instance
    @param str: byte array of serialized message
    @type  str: str
    """
    try:
      end = 0
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      self.remote_username = str[start:end]
      start = end
      end += 4
      (self.battery_capacity,) = _struct_f.unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      self.power_state = str[start:end]
      start = end
      end += 1
      (self.battery_low,) = _struct_B.unpack(str[start:end])
      self.battery_low = bool(self.battery_low)
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      self.tell_remote_user = str[start:end]
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      self.phone_home = str[start:end]
      return self
    except struct.error as e:
      raise roslib.message.DeserializationError(e) #most likely buffer underfill


  def serialize_numpy(self, buff, numpy):
    """
    serialize message with numpy array types into buffer
    @param buff: buffer
    @type  buff: StringIO
    @param numpy: numpy python module
    @type  numpy module
    """
    try:
      _x = self.remote_username
      length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
      buff.write(_struct_f.pack(self.battery_capacity))
      _x = self.power_state
      length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
      buff.write(_struct_B.pack(self.battery_low))
      _x = self.tell_remote_user
      length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
      _x = self.phone_home
      length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
    except struct.error as se: self._check_types(se)
    except TypeError as te: self._check_types(te)

  def deserialize_numpy(self, str, numpy):
    """
    unpack serialized message in str into this message instance using numpy for array types
    @param str: byte array of serialized message
    @type  str: str
    @param numpy: numpy python module
    @type  numpy: module
    """
    try:
      end = 0
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      self.remote_username = str[start:end]
      start = end
      end += 4
      (self.battery_capacity,) = _struct_f.unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      self.power_state = str[start:end]
      start = end
      end += 1
      (self.battery_low,) = _struct_B.unpack(str[start:end])
      self.battery_low = bool(self.battery_low)
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      self.tell_remote_user = str[start:end]
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      self.phone_home = str[start:end]
      return self
    except struct.error as e:
      raise roslib.message.DeserializationError(e) #most likely buffer underfill

_struct_I = roslib.message.struct_I
_struct_B = struct.Struct("<B")
_struct_f = struct.Struct("<f")
class telo_state(roslib.message.ServiceDefinition):
  _type          = 'zagrosControl/telo_state'
  _md5sum = '8de8676759a8236f5fc5160d66f6ecf1'
  _request_class  = telo_stateRequest
  _response_class = telo_stateResponse
