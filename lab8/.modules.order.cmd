cmd_/home/qkmei/Code/KernelKraft/lab8/modules.order := {   echo /home/qkmei/Code/KernelKraft/lab8/chardev.ko; :; } | awk '!x[$$0]++' - > /home/qkmei/Code/KernelKraft/lab8/modules.order
