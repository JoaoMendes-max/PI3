set num_facs [gtkwave::getNumFacs]
set found {}

for {set i 0} {$i < $num_facs} {incr i} {
    set name [gtkwave::getFacName $i]

    # clk do TOP apenas
    if {$name eq "TOP.clk_i"} { lappend found $name; continue }

    # sinais directamente em lsu_i (sem sub-modulos)
    foreach sig {st_translation_req mmu_vaddr pmp_translation_valid} {
        if {[string match "*ex_stage_i.lsu_i.$sig*" $name] &&
            ![string match "*lsu_i.*.*$sig*" $name]} {
            lappend found $name; break
        }
    }

    # entradas e sinais internos do bloco pmp_data_if
    foreach sig {lsu_is_store_i lsu_vaddr_i pmp_access_type data_allow_o} {
        if {[string match "*i_pmp_data_if.$sig*" $name]} {
            lappend found $name; break
        }
    }

    # mcause e mtval nos CSRs
    foreach sig {mcause_q mtval_q} {
        if {[string match "*csr_regfile_i.$sig*" $name]} {
            lappend found $name; break
        }
    }
}

puts "Sinais carregados: $found"
gtkwave::addSignalsFromList $found
