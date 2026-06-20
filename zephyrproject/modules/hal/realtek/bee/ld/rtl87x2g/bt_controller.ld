SECTIONS
{
    PROVIDE(BB_read_baseband_register = 0x00070a3d);
    PROVIDE(BB_write_baseband_register = 0x00070a75);
    PROVIDE(BB_read_native_clock = 0x00070ae9);
    PROVIDE(BB_read_native_counter = 0x00070b37);
    PROVIDE(bzdma_ble_set_segment_valid_bitmap = 0x00071401);
    PROVIDE(bzdma_send_burst_rxcmd_and_wait_complete = 0x000720fd);
    PROVIDE(vhci_has_sig_pended = 0x00073eb5);
    PROVIDE(BTMAC_Handler = 0x0007a93d);
    PROVIDE(btmac_pm_check_inactive = 0x0007ace7);
    PROVIDE(btmac_pm_initiate_wakeup = 0x0007ad2d);
    PROVIDE(btmac_pm_set_power_mode = 0x0007ad49);
    PROVIDE(btmac_pm_get_power_mode = 0x0007ad55);
    PROVIDE(__aeabi_memset = 0x0007e775);
    PROVIDE(bzdma_supported_le_max_seg_num = 0x0013ea89);
    PROVIDE(bzdma_send_packet_to_ble_data_ring_fifo = 0x0013edb4);
    PROVIDE(lowerstack_SystemCall = 0x0013f54c);
    PROVIDE(vhci_ack = 0x0013f7a4);
    PROVIDE(vhci_ack_nowake = 0x0013f7a8);
    PROVIDE(vhci_close = 0x0013f7ac);
    PROVIDE(vhci_open = 0x0013f7b0);
    PROVIDE(vhci_send = 0x0013f7b4);
    PROVIDE(Bzdma_Manager = 0x0013fb54);
    PROVIDE(g_modem_psd_report_array = 0x0013ffd8);
    PROVIDE(rcp_BB_handle_psd_end_intr_func = 0x00141218);
    PROVIDE(rcp_BTMAC_Handler = 0x00141230);
}