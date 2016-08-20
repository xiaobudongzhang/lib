;; This buffer is for notes you don't want to save, and for Lisp evaluation.
;; If you want to create a file, visit that file with C-x C-f,
;; then enter the text in that file's own buffer.

(+ 2 2)

(+ 3 (+ 1 2))

(setq my_name "badDog")

(insert "hello!" "sb")


(insert "hello i am" my_name)
;函数定义
(defun hello()(insert "hello i am" my_name))

(hello)

(defun hello(name)(insert "hello" name))

(hello "you" )

;开启缓存新窗口
(switch-to-buffer-other-window "*test*")
;多条命令绑定
(progn
  (switch-to-buffer-other-window "*test2*")
  (hello "you"))

(progn 
  (switch-to-buffer-other-window "*test2*")
  (erase-buffer)
  (hello "there")
  (other-window 2)
)

(let ((local-name "you"));两个括号变量赋值
  (switch-to-buffer-other-window "*test*")
  (erase-buffer)
  (hello local-name)
  (other-window 1)
)

;格式化

(format "Hello %s\n" "sb")

(defun hello(name)
  (insert(format "Hello %s\n" name))
)

(hello "ssb")

(defun greeting(name)
  (let ((your-name  "byz"));多个命令连接
    (insert (format "hello %s!\n\n I  am %s."
		    name
		    your-name
		    ))
   )
)

(greeting  "you")

(read-from-minibuffer "Entern your name:");从stdin读取



(defun greeting(name)
  (let ((your-name  (read-from-minibuffer "Enter your name:")))
    (insert (format "hello %s!\n\n I  am %s."
		    name
		    your-name
		    ))
   )
)

(greeting "bastien")

(defun greeting(from-name)
  (let ((your-name(read-from-minibuffer "Enter name:")))
    (switch-to-buffer-other-window "*test*")
    (erase-buffer)
    (insert (format "\nHello  %s\n  I am %s"  your-name from-name))
    (other-window 2)
   )
)
(greeting "tesdf")

;;3

(setq list-of-names '("aa" "bb" "cc"));列表变量
(car list-of-names);第一个变量
(cdr list-of-names);剩余变量 不改变变量

(push "aapre" list-of-names)

(mapcar 'hello list-of-names);循环传参数


(defun greeting()
  (switch-to-buffer-other-window "*test*")
  (erase-buffer)
  (mapcar 'hello list-of-names)
  (other-window 2)
)
(greeting)


(defun replace-hello-by()
  (switch-to-buffer-other-window "*test2*")
  (goto-char(point-min));定位到缓存开头
  (while(search-forward "hello" nil t);nil 范围不限 t不提示
    (replace-match "hi")
  )
  (other-window 1)
)
(replace-hello-by)



(defun bod-names()
  (switch-to-buffer-other-window "*test2*")
  (goto-char(point-min))
  (while(re-search-forward "hello \\(.+\\)" nil t)
    (add-text-properties(match-beginning 1)
			(match-end 1)
			(list 'face 'bold)
    )
  )
  (other-window 1)
)

(bod-names)
