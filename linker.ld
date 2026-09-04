MEMORY
{
  dport0_seg :    org = 0x3FF00000, len = 0x10
  dram_seg  :    org = 0x3FFE8000, len = 0x18000 - 0x400
  iram_seg  :    org = 0x40100000, len = 0x8000
}

ENTRY(_etssos_boot_entry);

SECTIONS
{
  .text :
  {
      *(.text*)
  } > iram_seg

  .bss (NOLOAD) :
  {
    *(.bss*)
  } >dram_seg

  .data :
  {
    *(.data*)
  } >dram_seg

  .rodata :
  {
    *(.rodata*)
  } >dram_seg
}
