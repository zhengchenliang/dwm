#!/bin/bash

. ~/.base-dwm-color

tmpr() {
  tmpr_cpu=$(sensors | awk '/Package/{print $4}')
  tmpr_mem=$(sensors | awk '/nouveau/{a=NR+3}{if(NR==a)print $2}')
  tmpr_dsk=$(sensors | awk '/nvme/{a=NR+2}{if(NR==a)print $2}')
  printf "TMPR: cpu/mem/dsk=${tmpr_cpu}/${tmpr_mem}/${tmpr_dsk}"
}

proc() {
  cur_proc=$(awk '{print $4}' /proc/loadavg)
  printf "PROC: cur/tot=$cur_proc"
}

cpu() {
  cpu_tmp=$(iostat | awk '/avg-cpu/{a=NR+1}{if(NR==a)print $0}')
  cpu_sys=$(echo ${cpu_tmp} | awk '{print $1}')
  cpu_usr=$(echo ${cpu_tmp} | awk '{print $3}')
  printf "CPU: usr/sys=${cpu_usr}/${cpu_sys}"
}

memo() {
  mem_used=$(free -h | awk '/Mem/{print $3}')
  swp_used=$(free -h | awk '/Swap/{print $3}')
  printf "MEMO: mem/swp=${mem_used}/${swp_used}"
}

iost() {
  nvme_tmp=$(iostat | awk '/nvme0n1/')
  nvme_spdr=$(echo ${nvme_tmp} | awk '{print $3}')
  nvme_spdw=$(echo ${nvme_tmp} | awk '{print $4}')
  sata_tmp=$(iostat | awk '/sda/')
  sata_spdr=$(echo ${sata_tmp} | awk '{print $3}')
  sata_spdw=$(echo ${sata_tmp} | awk '{print $4}')
  # case ${nnj} in
  #   0) printf "O: nvme/sata=${nvme_spdw}/${sata_spdw} kB/s" ;;
  #   1) printf "I: nvme/sata=${nvme_spdr}/${sata_spdr} kB/s" ;;
  # esac
  printf "I: nvme/sata=${nvme_spdr}/${sata_spdr} kB/s O: nvme/sata=${nvme_spdw}/${sata_spdw} kB/s"
}

timi() {
  time_now=$(date '+%H:%M:%S.%3N')
  printf "^c$cr1black^ ^b$cr1white^ TIME: ${time_now}"
  printf "^c$cr1black^ ^b$cr1green^ CPU"
}

nn=0; nnj=0
while true; do
  nnj=$(expr ${nn} % 2)
  sleep 1 && xsetroot -name "$(tmpr) $(proc) $(cpu) $(memo) $(iost) $(timi)"
  nn=$((nn + 1))
done

