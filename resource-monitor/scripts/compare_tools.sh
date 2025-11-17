#!/bin/bash
# Script para comparar ferramentas externas (exemplo)
echo "Comparando resource-monitor com htop..."
htop &
./resource-monitor --profile $$
