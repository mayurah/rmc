

#ifndef __rtrDistContProt_h
#define __rtrDistContProt_h

#include "rtr/platform.h"
#include "rtr/rtdataty.h"

// Container message information
// length opcode flags Hdr Len
// |-|-|  |-|-|   |-|    |-|

extern DEV_SH_LIB_EXPORT const char *rtdistcontProtNames[]; 

const u_16 rtdist_cont_header_len = 6;
const char rtdist_MDA_ID = 2;
const char rtdist_RVA_ID = 3;
const char rtdist_NEWS_ID = 4;
const char rtdist_NDS_ID = 5;

const u_16 rtdist_cont_wildcard = 0;
const u_16 rtdist_cont_prot_id = 1;
const u_16 rtdist_md_prot_id = 2;
const u_16 rtdist_rva_prot_id = 3;
// Skipping 4
const u_16 rtdist_nds_prot_id = 5;		// needs to match rtdist_NDS_ID

const u_16 rtdistcont_maxprotid = 5;

const u_16 rtdistcont_authlogin = 1;
const u_16 rtdistcont_login = 2;
const u_16 rtdistcont_login_response = 3;
const u_16 rtdistcont_agent_table_req = 4;
const u_16 rtdistcont_agent_table_response = 5;
const u_16 rtdistcont_heartbeat = 6;
const u_16 rtdistcont_ping_request = 7;
const u_16 rtdistcont_ping_response = 8;
const u_16 rtdistcont_login_nak = 9;
const u_16 rtdistcont_new_ticket_request = 10;
const u_16 rtdistcont_ticket_expired = 11;
const u_16 rtdistcont_new_authlogin = 12;
#endif
