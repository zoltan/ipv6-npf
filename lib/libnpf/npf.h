/*	$NetBSD: npf.h,v 1.1 2011/02/02 02:20:25 rmind Exp $	*/

/*-
 * Copyright (c) 2011 The NetBSD Foundation, Inc.
 * All rights reserved.
 *
 * This material is based upon work partially supported by The
 * NetBSD Foundation under a contract with Mindaugas Rasiukevicius.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE NETBSD FOUNDATION, INC. AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _NPF_LIB_H_
#define _NPF_LIB_H_

#include <sys/types.h>
#include <net/npf.h>

#ifdef _NPF_TESTING
#include "testing.h"
#endif

__BEGIN_DECLS

struct nl_config;
struct nl_rule;
struct nl_rproc;
struct nl_table;

typedef struct nl_config	nl_config_t;
typedef struct nl_rule		nl_rule_t;
typedef struct nl_rproc		nl_rproc_t;
typedef struct nl_table		nl_table_t;

typedef struct nl_rule		nl_nat_t;

#define	NPF_CODE_NCODE		1
#define	NPF_CODE_BPF		2

#define	NPF_PRI_NEXT		(-1)

#define	NPF_MAX_TABLE_ID	(16)

nl_config_t *	npf_config_create(void);
int		npf_config_submit(nl_config_t *, int);
void		npf_config_destroy(nl_config_t *);

nl_rule_t *	npf_rule_create(const char *, uint32_t, u_int);
int		npf_rule_setcode(nl_rule_t *, int, const void *, size_t);
int		npf_rule_setproc(nl_config_t *, nl_rule_t *, const char *);
bool		npf_rule_exists_p(nl_config_t *, const char *);
int		npf_rule_insert(nl_config_t *, nl_rule_t *, nl_rule_t *, pri_t);
void		npf_rule_destroy(nl_rule_t *);

nl_rproc_t *	npf_rproc_create(const char *);
bool		npf_rproc_exists_p(nl_config_t *, const char *);
int		npf_rproc_insert(nl_config_t *, nl_rproc_t *);

#ifdef _NPF_PRIVATE
int		_npf_rproc_setnorm(nl_rproc_t *, bool, bool, int, int);
int		_npf_rproc_setlog(nl_rproc_t *, u_int);
#endif

nl_nat_t *	npf_nat_create(int, int, u_int, npf_addr_t *, int, in_port_t);
int		npf_nat_insert(nl_config_t *, nl_nat_t *, pri_t);

nl_table_t *	npf_table_create(int, int);
int		npf_table_add_entry(nl_table_t *, npf_addr_t *, npf_netmask_t);
bool		npf_table_exists_p(nl_config_t *, u_int);
int		npf_table_insert(nl_config_t *, nl_table_t *);
void		npf_table_destroy(nl_table_t *);

int		npf_update_rule(int, char *, nl_rule_t *);
int		npf_sessions_send(int, const char *);
int		npf_sessions_recv(int, const char *);

__END_DECLS

#endif	/* _NPF_LIB_H_ */
