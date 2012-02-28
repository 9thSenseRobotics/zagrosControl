; Auto-generated. Do not edit!


(cl:in-package zagrosControl-msg)


;//! \htmlinclude telo_state.msg.html

(cl:defclass <telo_state> (roslisp-msg-protocol:ros-message)
  ((remote_username
    :reader remote_username
    :initarg :remote_username
    :type cl:string
    :initform "")
   (battery_capacity
    :reader battery_capacity
    :initarg :battery_capacity
    :type cl:float
    :initform 0.0)
   (power_state
    :reader power_state
    :initarg :power_state
    :type cl:string
    :initform "")
   (battery_low
    :reader battery_low
    :initarg :battery_low
    :type cl:boolean
    :initform cl:nil)
   (tell_remote_user
    :reader tell_remote_user
    :initarg :tell_remote_user
    :type cl:string
    :initform "")
   (phone_home
    :reader phone_home
    :initarg :phone_home
    :type cl:string
    :initform ""))
)

(cl:defclass telo_state (<telo_state>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <telo_state>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'telo_state)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name zagrosControl-msg:<telo_state> is deprecated: use zagrosControl-msg:telo_state instead.")))

(cl:ensure-generic-function 'remote_username-val :lambda-list '(m))
(cl:defmethod remote_username-val ((m <telo_state>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader zagrosControl-msg:remote_username-val is deprecated.  Use zagrosControl-msg:remote_username instead.")
  (remote_username m))

(cl:ensure-generic-function 'battery_capacity-val :lambda-list '(m))
(cl:defmethod battery_capacity-val ((m <telo_state>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader zagrosControl-msg:battery_capacity-val is deprecated.  Use zagrosControl-msg:battery_capacity instead.")
  (battery_capacity m))

(cl:ensure-generic-function 'power_state-val :lambda-list '(m))
(cl:defmethod power_state-val ((m <telo_state>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader zagrosControl-msg:power_state-val is deprecated.  Use zagrosControl-msg:power_state instead.")
  (power_state m))

(cl:ensure-generic-function 'battery_low-val :lambda-list '(m))
(cl:defmethod battery_low-val ((m <telo_state>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader zagrosControl-msg:battery_low-val is deprecated.  Use zagrosControl-msg:battery_low instead.")
  (battery_low m))

(cl:ensure-generic-function 'tell_remote_user-val :lambda-list '(m))
(cl:defmethod tell_remote_user-val ((m <telo_state>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader zagrosControl-msg:tell_remote_user-val is deprecated.  Use zagrosControl-msg:tell_remote_user instead.")
  (tell_remote_user m))

(cl:ensure-generic-function 'phone_home-val :lambda-list '(m))
(cl:defmethod phone_home-val ((m <telo_state>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader zagrosControl-msg:phone_home-val is deprecated.  Use zagrosControl-msg:phone_home instead.")
  (phone_home m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <telo_state>) ostream)
  "Serializes a message object of type '<telo_state>"
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'remote_username))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'remote_username))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'battery_capacity))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'power_state))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'power_state))
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'battery_low) 1 0)) ostream)
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'tell_remote_user))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'tell_remote_user))
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'phone_home))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'phone_home))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <telo_state>) istream)
  "Deserializes a message object of type '<telo_state>"
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'remote_username) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'remote_username) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'battery_capacity) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'power_state) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'power_state) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:setf (cl:slot-value msg 'battery_low) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'tell_remote_user) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'tell_remote_user) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'phone_home) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'phone_home) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<telo_state>)))
  "Returns string type for a message object of type '<telo_state>"
  "zagrosControl/telo_state")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'telo_state)))
  "Returns string type for a message object of type 'telo_state"
  "zagrosControl/telo_state")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<telo_state>)))
  "Returns md5sum for a message object of type '<telo_state>"
  "b19c6fe489b2b2906e73c9577a122021")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'telo_state)))
  "Returns md5sum for a message object of type 'telo_state"
  "b19c6fe489b2b2906e73c9577a122021")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<telo_state>)))
  "Returns full string definition for message of type '<telo_state>"
  (cl:format cl:nil "string remote_username~%float32 battery_capacity~%string power_state~%bool battery_low~%string tell_remote_user~%string phone_home~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'telo_state)))
  "Returns full string definition for message of type 'telo_state"
  (cl:format cl:nil "string remote_username~%float32 battery_capacity~%string power_state~%bool battery_low~%string tell_remote_user~%string phone_home~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <telo_state>))
  (cl:+ 0
     4 (cl:length (cl:slot-value msg 'remote_username))
     4
     4 (cl:length (cl:slot-value msg 'power_state))
     1
     4 (cl:length (cl:slot-value msg 'tell_remote_user))
     4 (cl:length (cl:slot-value msg 'phone_home))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <telo_state>))
  "Converts a ROS message object to a list"
  (cl:list 'telo_state
    (cl:cons ':remote_username (remote_username msg))
    (cl:cons ':battery_capacity (battery_capacity msg))
    (cl:cons ':power_state (power_state msg))
    (cl:cons ':battery_low (battery_low msg))
    (cl:cons ':tell_remote_user (tell_remote_user msg))
    (cl:cons ':phone_home (phone_home msg))
))
