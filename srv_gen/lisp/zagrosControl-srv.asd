
(cl:in-package :asdf)

(defsystem "zagrosControl-srv"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "telo_state" :depends-on ("_package_telo_state"))
    (:file "_package_telo_state" :depends-on ("_package"))
  ))