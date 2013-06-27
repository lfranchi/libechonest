 /****************************************************************************************
  * Copyright (c) 2010-2012 Leo Franchi <lfranchi@kde.org>                               *
  *                                                                                      *
  * This program is free software; you can redistribute it and/or modify it under        *
  * the terms of the GNU General Public License as published by the Free Software        *
  * Foundation; either version 2 of the License, or (at your option) any later           *
  * version.                                                                             *
  *                                                                                      *
  * This program is distributed in the hope that it will be useful, but WITHOUT ANY      *
  * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A      *
  * PARTICULAR PURPOSE. See the GNU General Public License for more details.             *
  *                                                                                      *
  * You should have received a copy of the GNU General Public License along with         *
  * this program.  If not, see <http://www.gnu.org/licenses/>.                           *
  ****************************************************************************************/

#include "SongTest.h"

#include "Config.h"
#include "Song.h"

#include <QDebug>
#include <QNetworkReply>

QByteArray code = "eJzVnQGS7aqSXackCQFiOIBg_kPwWpSjn_0jREW44kW33e7s_6vqniOhzJ17k0nqOI4jHhsTzp25086kuTMl7UwbOzPSxpwh70ydG3Nd987c786UnQkp7cz7bsx9hJ3Jc2fqsTO9bEwMc2e88G_zjJ3xtj5N4sY25mo709-NyXzExpxtZ3LamXJtzHPHnXmOnRnXxhQf8rfxy79NCzszysZUl_PbjHtjmsv5bWramH7lncnnzpS6M_3YmZE35q11Z1iRb-NT3Jhw7Ux8dkY4_DTzKDsT687wF5_mPK6-M_e1M8_cmZo35sRrN6bPjblYzo1hOTcmz53pY2dm2phwtJ2JW7M-4Mvcd9iZGHemhJ1pbWfw-W8Tc9uZ_uzM2zcm4fLfJuu23-YdG_NAlDaGKN2Y0HZmjo0pfMHGXHVnSOAbE9-dedrOjLkxNcSdiX1n8rUz492YFsfG9KPuTOs7owt8G0Pt07zQjo255s7EtDPe9KcZwMfGPHlj5nXuDMR_YyAdG9PytyFYrp25ys7cc2POtDXIkY0Z58ZcZ9yZMDZGWfBp_qja8s78i6otb8wZnp158sb8osty3Jm-NePdmJDixtz65rd5ws7UuDP_nmojVX6blN-dgc58m6x0-zYh7EzqG_NIV79NzDuzPuDTlLIzPWxMUax8mzfszKgbUxUN34Y0-22ay_ltvOlvo2T8NL_osufemVp2xiX5NvPZmFcJ9W3cpvo2I2zMOPrO7FVb25kZw86U89uQc96dkbx_m3rtzDg25pSSfBsW7NuYvjcmhJ1R9n2aAIHbGEXht5HsfJpf9FGqO1PunaltYyLRsjFP35l27EyvO7PXVv7Jt5lhY_J974wL9m22qu2Rcn6buDU1bkw5351B2W1M2Zq9elJQfpu9tiLtbExvG9O8rW8jP_s0XVj6Nm4JfJved-adG_NCor_NuK6dMYi_Tco786SNmSSHjbnzzuTwba4jXDsT6848Y2dm3xiRZ2P6uTNb9RTOtjN33Zkxvs0f1dO-5jV2psSd-UvN69mad2d-qXn9op7Czoy-MSFsTQo789aNuZUU3yaeO_OXehnpbmP22iocO3PPjfmlbrVVT_u6VW5lY35RXntt1e6NKantzL6qBfXbmPfcmdE25peqltL827hg3wbA-zb9aDuzV15u23wby1PfZq-tSFobs9dWpPeNsfL1aUa4N2bq8t_mvnYmlZ1p-dsgoe6d2WuruTOnROnbjGtjLgJxY0hoG1PLzsy4Mabojdkrr1g25gY8NqaOjYnogo35RT3dO7PVR3GWjUmzbUz2UXybu-0MbrsxCo5P84S8M2VsTJFEfxtLLt_mCTtjqH2aSnrfmK3GqaNvzF4BdcJpY5Sb3yZdO5PTzuzV014fXXFn5rsxv9SPQt2ZGDZmCgDf5o47YyH3y7CW986EujOy5E9jd8HG3GVnIP4bA4R_G0F6Y2LamTw3JrT4bf4_rT1t1dMxd2avrerYma3ywjM35jddtjNBcfZtbO_6NnttdW3N9vH-RVulq-_M0t6fZt8T-Af19Fvtqe6MHSDfpj4744V_mpLqzvyinp6dscT0bSzkfpoqef80DaD9Nl3_-TYu57fZK6BfKlN7fZQ35k_6yEfxbbbqaRx1Z9xO-DYx7Ywtpd_GMu-nmWffmX0_YT13xuavb7PXVpYRvo3tbN9mnBvzSz_hX-pWlnq-DS7_be4j7cw1duaXmte7MyVuTKx9Z_a1Jx_jp8ln2RkbTr_NX9QTKXpjwrMz9d2YX7r-UtwZpeqnqQbTt7GU92n-VCH6RR_dO_NL_WhrLD9-mrdtzfvsjO2Zn2ac585cz87stZVq59NMmxm_zS_K69kZ4fDL_KKeyP47s689Kd2-zb6vr507Q-r4Nr-opzvsTIzf5o_a6i-Vqa22-ot62usjG5o-zZ9OY2310VX6zmyrWiFdO7PXVn1r9sorXjuz11Y2f32a-Lw7Y3Hj0yS7Rz6NiXRjUtuZP1Wmnp2R6n6bfcegxZxP80vdykv7NuPZmN_OW8WN-a0yVTfmt9pT35k_aas_1J7-Z6qnrT4a896YXypTe_W0r0x5sObbbJWXSWdjrq2B-23Mair8Mr_VrXba6lqHvT7N2Jm9Lrs9tPFt9trKIyzfxkLft7GB69NED5l9GvvUNybHnVFef5t_T5d505_ml9NYS5x9Gg_HfBpB-tv8UntKW_OL8vrXevMUHN_mL9rql968rUlpZyzGfpt27cycGzMI1I0xID7Nb-pp29fnsbkvcx2h7MxeWz15Z-rcmF_OPbW-M_u61VY9XTVtTIDqfhq1zM78d6mnf68ytZ908ZaN-UvXXzi3Zq-Pct4Zl-TT_NK55xiGb0NS-jYxjJ3ZT6sgtWxMKDvjMf1Pk8-8M5Yvvo3k_duIS5_mkdp_m70-sij6bdq5Mb_Urfbq6Ze-vrQx9ac89WGahc1P84s-sqPp2-zrVv9d6smWw0_zP1Qf7atLd9sZKMmn-bWvb1uZGm1nJB2fRqXzbS6LOd8m9535RR-9OzPPjfmlbpXaxtzS82_j8bVv46P4NsDhxuzV01s2Jlk0-zZX2RkF5afJ4d4Z2xW_zf5UlC1a3yZeO-PG7LexiPRtPOr3aYp85dvslZfNX9_m36tqke42Zq-89urJTY5v88tMib4ze330l6qWbYPf5p47I9P9NL-pp_5truN-d-ZfU0_HuzPugG3MX7TV8ezMvm7lMbIv8z-1MvWLtoob85e-vuuKO3P3ndmfqNpXpv69E1Xt2plfKlP_77ostq3ZK6_QdkY58ml-q0xtz0xJhD_NL7Wn-O5MCTuzSltfpnjc59vstZUB8WmqQwu-jQMtvo0P6tM0y0Sf5t_UR3_o3PufWV3a9-Z59O3b_EV57bTVb5MAf-nrKzvjQYRPc9nS8m329aNfpvnt9dF2mt9eH_nxn-a36tJf9FHZmfJuzJ9OVCk3Pw3LtTPbytS_V10ylr7NL-rpF300NqaEtDNpa7Zdf0XH_DTVIRzf5i_a6i_qyRLxt9lPjXCj4tO8V9uZP6inX_RRKTvTxsb8Vns6d-Z5v83l2fON-UUBpZ3Z9_Xdz8Z4dHVjbNP6Nn9SQH-pLu3PPf03VZf29aM4d-bNG_NLdemXqRHbmXtP2xlLW5_mTzplXyFK985s--t-mXbuo_g2UrBPk8-6M3_ovvuTxnEf8tv0vDG_aJw1OuLTvG1jflMxdWPauTW_zHbIO3O1nYlhZ_YKyLLYt_lvmvzwJwW01zi_qJi6M0rVL_ObxtnXj9w6_TS_nDCyyPBt9hrnl3nmu_rRb6eTzp2xpPZpfjt_tFUxDh74NPGsOyNt_DTJAtS38VjGt-lpZ3C9b_OLitl3wUlXv80vVZ7t7DvHw38bS3nfZlvHKQ4O-TR_q_L8pYNua8bO9HNrfjnZtNc4-5NNcWNev_zT_KJE-rEz496Yf_H8kUcMv81e4_xrOuWEvG_ML7Mdtsahfd-m7Uyo3ya-xPBb3usIR4uxX2O8MR4xQieulPLo6SnDH9f3vq8Uc7ze6yznbOVObZajj_D0J_Qj9nGHa5yt8HSf-w3PPNtbcrp6dWcXEsKf55ZgQWn92wAPG-U63-cp-R4lzFGvp7bzefN1tzvE1ut9n3eod-j96p5qi9f5nPmR4I0cAzr86TWEq1513CmfWamSYok5e2pz_bO1_5SstN3Fa729slxjvuc77zCgKe0825pFFst8HtYj9zziebcx4rhbflsdNdzX0Ut63ifcc0TWsNQWnrfF-33me14tlhzqzLGXqwIIISR0SG4wjtcgr_29K1DPpedxxMlSh55KGnngXTxK8La0yrKkftbWY6lPu7w5R8SPMI_59CvOK44-uYr2pPK84fSdQu-TE2ve0uC-auZj7hcCxmM57bGdvV6Zx9KuVPvdHh4TKz15ElxNdE-ixzP32MYFl-RRvYcb47j1-8QRzjdwi-cR0uzrj_tz3c_67Qx81PrtMArWb6-zXjPqBuu3ENvS0xXv_E57IfzkEkdiHeEm8WXtW2GV3uPhV7pKOoDT0lmRO8wr43499VnfEsJd540jDJhLG-ElKntuLR-pkoG5G7TOjM_V8bR65vE8T3vPeEzfKBJvqfAbUzmvcZN1uYgeUkuw62QQ1xHq5cDQnst4ZkkTr8w85aNmEqlDw_iX7z1TrKOHNnjiOaXIo54sUpstvDyB457e0hvuhgO4-9nKWULjGuXMKbceZn2MiHeikSp_wEXhDXM8eVwplMdFB3Vmyu9b-tvxiLI-pr2-6ik4APh4cMqC0uWZ4fshVrJUn6wRkY3X5Psd9_2Mi6XkKksKR651xvKcZ0y2D1TUDi7J_z8nTKKPh3-GA_KUCs8uZELkud4HXdtKPiKP6loTHNpNiLSU7o56LFfiiY_ysO6sC8otslJET-JqU2qjsy7PfXE5aRIq5SKOidcUau_hrYiMMm5iuvFsCQC-7UrjxhXLLKS_cNbniuf1gAaxEX2sSc8AAb9kHVvEL8OLQibOSgGplv9NQosQ4enk9mQ-lRhC-iViCTdIk2WeqNuOzkwtvrMRR_c9K44FAo02eFqPy_fkzA95ltcc4I8f1J8jOxzHvSJC4pj17L57gqCCcA_SowQI_8_5zqz4fbL0Vw7zPEMOpcx89zs0BwvUBEbwa5TlWQC8zrdPETInZ0KxOuHET09-0i6clifB1bdrXI0leOf1jJzuQr7Wk8An3OqOMCzrfAc-GMJTj5vHzUfF_CbQe3YYdg8VcHuuzPfiH_fgzmq-E5GdCNQhP-gz9zAy0J_gAx2ImDdLjY-VyzdXRLAr16O3O_GA7x4j18TC8TPyKRAYn5OnSCg2lqCBr8QvFK7iMDgxoMMSjObqzNqfGFk6nsY4Qn4IgpsAeCqoVYFdgiM33Obx3V59lloaQJZ6eSOUEbjjhsFYoLm_NYyb_-mlBi4YECxg4c3i4yjnhfPzH-Z199Fw0pM8qVv02Qx6_jIWyCAIT5qYgBKRHh9iJjTg7Ol8mM7ROzd4IesCHvaQmxroAwqRGojW8vBYgcxyNR9BXZnzvTLZhpCDtg0yb0kkIZaIgLsmoHzp4ERTAOUBxkRSxMsri9ES0ccyANpy-icBjA93FwXL11gOffWhAUSE3Kyx3jh15tnzVetmYgQfFz6HA1cag7U9Gl9PQui-eGHkgpu9rDFJ-r3GvIx5oLD0m_-SAUwS_JHBW9IDMUWUsPYXcV34cn1jXBlqwC3ewM0R-EPQ4LxeMTGE0yY7gB5UGNkXWkWu870S0QC2PZXgBx5fPPitB17cuVjum4-5H7w744uk-yPdranU4Fzl4gta5zJIh1coZPALGO7N6CSxsQIHTiTVCQO8vll1sLZ10GimvrIMXmdzH9ky8GN8lwfNlbijgs_xLZ37ZwFZxQtkrfMi8b8RXQ04I72vSWwieEojd10A83Ue7cp8zEXu4RG39F5XZaHILmm2_uJtvlyH-0rPHAEuBXANfkguO_Cq8zz4w5d1IrcLIw8-Dg24j0gOA78jFIYrJJlO0hfZ_xyTtS0OlCC_DunLCkTQ9Dzf9HJNgMp88uz5mvw4kLIGtwHaPu9d7llGfHjCsR0D_GOtSDDQv_uEMgVCG_5Q8FSIAc_3XR57dwjDwSIQqXCv5335aeN6yc3jLWAumhcil2GDLcLtJnFKJN0ZJgm6S4SgPIRSdL77W2aPeGSHwOCkNwsWEr90LABcDNJRB84J_Qtc4-0r_HDdJ3W4zukasyZ4G4tS5Jc846RfJtATrEjicCMDGpYj1VhIu9zYGao0gvSCG7F0Z-gvWbC8iGNoJHQKXzXw3_YAIzJCGC7pq1TSHJgyV3cZqWiYWNIEqcLFWg8cFAc-M6mSRFoGrgi5qLBFbo4Ae0rCdQgUWNTxjoPVsNoRY_XFhznhLeTKHO4MC3j4XcAVU8CxKtFrFfi4hSyH8MGBJ7njSXgciwBqtd5N0aFI1iQh702AxFafzPOBI3G_8yo3C3wd7X1TiCDiuDNI8MK41jsFbTMBhGp-M2F4SdESUM_1DXBwkoqI_tK5OyL_JmvOjEMjJ9ZMfSCpOIbmTCfsaYzWWdDCx83Jo86kNRbqWjezltM6YVuZ_c1AzdNmIHtmvDVF76E2WH05I_g_YcQzcRW1gv-zVZAcYLBKeT_m8QHzeW5ZIt9-4Q1kFwCJODpGy-gObo2FB1FBJZLc0YM7YQ9gjRsAK-TsCSSUec1AYHPj_XhfV5vbszsHLIcJsgTzhsJeotMVwCmAICRDgJt-UCuQNtYFLCLflso9pOGzIX3oZA2uMs3m5P3_MgTI0_7jZ_-YLM_hyslsEccKL4kC3cvCiE4xA9vd9GXqh9kibEOOOLHQzD0ARAl97sMR9Mjpg9iCeaNOIL7Iv8xd-VvwOSFDgCxgBl5AYug6JL84wQrCoB_8jBQKb7nCA-0OLvp9o2naC6W4gI5HDh-I9YPketwkE6CFB8FiIHtICgkGQxYSVE_i09JM4F8T58C4jgsAIp2gmuAfyZw8C7UwC9RcEXPosyFHWbcAMQXPjwSLKYUI8z4IJBYg-_oJP5kAMJ3G91n_LMsiIWD9OZ1hEIExYAk_kf1n1C7YiIs9SNWEdyFtvVPyB1RS8p4E-DLA4RIiH3e93AZQeBd0BDkY7TLLajUYcxwPIU14oq7xK-AGBCDz4fGlF1u9DzICzxEh0WXvSEgwukPfZJHgDahGAhs8_WOANujeR-RNBCDPBAyIiLBOXoxkDFIqogsCVdA2EXUNozL3z5dvAg_ehnIE_69G7gNIE4AzWRcglcSMHwfEY7G_ikXgHst9IEh5tqDZMEjJ3-QAIp08GQ94KUKdRPt07p8kjsgL3F1_y-3iWtLzAvDLWuCEBRgNsF9Ys6khI5HPCvbe6_VERAmclCsAiIc4jcDovkBmEoUqSzC2yPitUfRXNQugQg15PtdLrITaVJlIhHH2QaAiiABamcuFh3PBJEpYMzQGWpROd6XwUxQV2QcGBZ0pFwqJZxPnA1rVA9zA_6YsCw2fPNOTSLP4OExlkuUDIgvqD30h7Q3y2oiwfOhxRMUhCXsgRNYErAoMgjmwXwCQa6mo43JVcIfbfN7JL02nkNTLOVAsK_Sto_z4ogkR4YJhls9Dsu4KkADKvGYEaHV6dcCZ3U5RcJUZeZok114amNQOMBmHJejcSkW2EfEofKUe_wZ0I1LhkLNmhQxhBzstBX2Zy8RfuDx4du6KNhIjsPjC9ghKUPzgv97AcOXBBq69ZFL3BYLwiMnY6-WLbihwHwcBVNcTel812otcuCHFPBTYEk8o1tyC4J_66_tAUZv3k5MPsKiFIBlIVFIpxFRF-74kQrkbPBbZf4HMDT3HIo1EPLs1AKLALKNBRFjdpFOwe0EWrpMJAhJBinrrRCt2NOlpBkW2wSaHOSaovfnnkDxcDHhAFuKqBAnRTk7hAUbFizIJFneQBeu1TgYGVhK55YbFNU4u5gHKUMIwI57NCA9gQ_xMd4kGdBZc4qk-DZIPaAHxd-euAux79VLy3-GdZDtuDIjMJAJ-H1AcRfyDIr8s0ZyQZN-fQVCeSMwipIWXTE7i476ddvzUE2VI-JwxCsXAPuSPm3iRRDnyoAo43Mgr2bcDSbBQyTBx-KVYYwDrE4kwBdN59hDYKXm-eYAwiXS6gQQ5TqYwhF1I3j5XjKx3QwNO_EbIJg8Ix-8H4FcfAu-ACgOMSXzlEmECvi6Ay0GhQEwA3JTdOSQij9dZ5EAAtO_CRZBkDcUD8-0ZnIPj4O2BbEcagkMBXwFYwenOChsNK0YhNkj08v6ACEiIDuZquVWVfWzgL0vOn78tukN385_yA_CLgOQk5H06fj7xrdU9FEBtefLl1I6n4Jg3cpdvw386wV5y8r3dBWzJxCuxtbY6O6QY8CNTctcNRUoCAIwabDSROdyRRfuSseyZ5nlCx08pOcKxBxaQGzpmbvBd-Tp59ZEcvQhh91hRXCupV1QrGMsSHmAfgcU_qsQ-l2Hcgy1W0vsFOANWAcHIRb6E8uL0J3oAPMFByT0mUhw4FcgMZG1O-CLpysxcESVkZBUEEQvo9uGVuLOBZn6V6E63Nu0m0CAKMkDrhDbXEygGTRKwExfINlQgNBFYgyr2Cwc5su-WeWKHjTTxcd5kPdYIfnVMYpXsBWAgp0j3GXTqo1cIXQKWVncDWY-P4QGQaoP077lx5Y6sigPwIvaOEzZPuoXCh8uXOHOTXThiefsrGIK7AcxB3kVnkV094e0Pz_4kjxbAkuRtU5FJP4cLBs4d3BlwCxPVyjPgU1NcMmuGk9xwdqgbi5Byd0cLIUIU4mZ4DKKHeMPV1guGoq_J5hnB_fgHHZ6GBzx3961HkFqEng1JQ9kEbOC5kMGTZA9kr70AYLvGAJZkdcb7wBRwrFnXPqJ-BFnLAbeDunRDCGiGz2dAjrQt4CZvgFsHAsl84Sog-t1U5lwEHHUBPH4ozeOpIRggE_jUKymZyC-0ItI1A5Lx0G2U_RF1SaTzREE2xCzkH9ILCgGnoKUbnLg9j8gEme_V9lgR2KYKxHoY4NuBcgWqYGq4Ja7NB10wQji9W4V2wcdJRub63Woko_Z7SR8iAfbUXIsQXtD9esF0d7tfEQ2OTAQA4Ty6Kb-1p8t_mizyTkAS8I9EQxkXaPVAPotUCzHLCpwwOdJMvAirx32YC-fDSdHWF4LLXViTF_qW0EI393Oq4AcUjLtBy73ch4DyuGtpYwdBJqW237gcaWbl9LHaJt0JzG47QrrJ-awTJNgtsovHfyKfyFgPpI8EPUSisWYKIsVTJgNyS3g8zkbynNAkIMk3QSCEJ7RmOHS8kQNAczJDvCB6PC7dMbmBFsnLkO0cke_cHlQC3CCMiXgIfIFSB7dkoXT2Fp7jRfBFeDnedsL-O6waz31OMj8cAseIchqk0RxIt6fEtX2LE7hbcrf2j2mEUfqPn_1jyCTwUfexJzkf_oXPLrF-G-CyFVYeCgR7LU-98LTD_eZp98dzuGIAbOKCBhrrgQgEVhI6CxAJEKWcbigZcDBEVgOhzO0QvjcElXDsraG0gYd6EY0GV7MCJ1YcwL7bvG7pQzTBKSsRJF5w6b2U4D41vqhKAcjEOlc5ndF_CrE8pPdBTJC8EEY8ViSbCR4iFE7ckjAgWCD_fDyY-wIYt5wKPWNigkXEAxEOXLsjzmVY6SPX2Be-lttPcc_0iawvoIkQAQEeWMcDHb9ENIhsXh9Pdmnk45vUjtQnBV3kCJS2_XUA0fDVaojrdybLQ_BIXTyp2HnS4Ad0lNwHmnH5D4QezynjXCMUrB7Ao0hgTRp8rOTBHxffEQkogf9cI45uwoaJHbiwbXkF_7IkEMnQL7yHNVPNQkkEjTi6Mvl0GzrFcFXWupdr5IlYh1eEBnEI7yQKCBlUFaoY52V1HBzO0-BiI0Ai07NomUiIJNL4AEH8W4CWp5tb9GCPSZZU3k5y2_RQTeDm9S60OIkXoci1ck1ksEsffVgvMAXPtLh3SGiQK9lYO90blD251TAsSLqHwmp0qGviI5-8FhtYq4_KQHd2d3UqJ9CKZE4iEe2PwGDBWYd84GwBPLVmOKsFywuiQV5y8_CUKPTL4jDCdtxIGfdB57mYwGv3xonjuzCA6NrITDBFQIO17wOEZOHNCfBidzeBZC70vYg4cifYBR7zKNEqYaLH3V7oIJ8sJEFAwJOJRhaTb6sWyerqW3GX_FoN6D03nllkNW9901onMRN65HETTrgsrBiNiXo6eXYsC8nYBOde0uFJFgsCTkzBHRvi7roLgO94tFz0OwLKvZ4MP-twFe7UaulhbQV-BB0gXnAYnAJnRBTD7Iu17BDAa7cUK7SLPIqMnqfF1pZU7vI-Ah6RigwGZp0XguwKrVuzUY_0c5Vz3Qq5p3lg6DNPa_DFy0LF08g75IKMujaJHUsuJAt3E4aejzMjsXA72RJcCOe6Ziw1Qbdfvv3EuQgDL4NfQYdCJQoOYMbWxiCzhqSGkaRjsYJoIBECkv_tBYqfwfycSL1-nq04PBOorqpr3G7oIy9JIS8iM0NBLAtdYwZfgytZ5_nExY0h5_jmTaJgdeAabm3f67e4GWtDbiZXQ7CFNuguecl9tfKDz1CAd93We4XmIjW3yVHhRwKzL9AdunRZAhiraAVjPfNI45Jo8MfJdePZQE7v-VM14-rIBoBIfXD1G6KG2iRbusmMCLyhUveJ2s4LdyHh0w0V6B0w-S5o5k8jFCP3DBEbuIK7MIiIWdy2XohJ9KPBMrfUzjlZaQTCeiEj_5cIuG9yHytCRBOw61-s-wWmCDL-K4sLt3Br1x14fB5PHNZDuTWkw7pzvGiCFG6gHz_zlaxKlKdcirI2UOrgzoN6j1boXlX8tD4EseaJx1bdUcxQu5QqzOQlt7GoXPhqplhbq-AjGnXeJGlwFE0KWUm2h3DvwKNlNzCGtEkWxh4FqHHcTwYTr9rXKLo1OXcSwgfsLZ0zkEnG7Syqm8Tttv1FpBKEcFkU0RxkwlfmVg3fy20-wpCfVVkrCF3xdPyeK6_rmi83N8y8PBn3B83dK0IzSfjBN1n--5KxoICr-y24ZWCJGlndq4e34acACYKSZGlNcuaDpHCr0VhSMvqF76JuLhsZDqhAIa6QKQ-w6jY-7pncJLOoiyxBCqEnAmSLtYaHtfWuKZI2cT-Fv3iQFREDvvpo7Rpe0-02nAMl9KIUXqD0dJsdQCN3nNZ2JcNcSXph-28oaNPsEycqLzew3kcWe17IigcQKQawTQP84TGyJYVxWhNDPQ8bYwAOPDCosfgmf4WuaejXMxbCH-EzVh-WPTFKS4ghfD1HxCjuyRfDoUkLcNNxxGEd_QUxkNH82NCpkySE9MC6xQatONzldBtl4pD4jmmP1PvCZWCUGbx9uDxShwmETANRtYjr-5JgZeRr2M39WBvG-R6I0rROSTpHKJbRT9Mi4VvIUTxW_t0DOrUsJRn85zP4JelVYJ1Y3Bx68A7QoL-gKAkbegbJcSdMvgw0WrlMPPyT2CDDwjohJrh5J--_wDg5vYO31k9xJK4OD-qEg_vXfNddayTZo6JDcIgDYkXcdqOrpueGX4NsVxbxkOtwJTSpWyNoUYtmCVltf22Aj8GduWiCIb6k8IEQLNm6TSYRRQtnpCe8hasS_UD8mxXE8x-B5oIeDiIve8YD6bACMRsccBiCJJbVMIBQcai_G_TCiM0Zia-oHfJfAMx39Xc95C8EWwuHFZ4wLMOjk3NVt0ZTCGSI1TI2YDkoOKj_Q8qFDr0jgjmKCvSq8pS_fsiZ5-tOrkdIKj41uRpbqmpWhbjHBG-Cj1vShAX9w31ueGzjQc1smfOHAMkqhp1vLHWWJvANwC_A2YJtCjhJBsAeN8ogrPmKK53DfC6rDyyUonjaJsLP3Y2GIN05WnKZj0ldeQzzxHNAJLeq4CWsOGkUzYGsz94rupKghDujry9bgKYFkPNIP8ngefgsOJC74ie0udxEG-hmnwBSICO0TDM8GNKAhcdA1GU4T2n8GZfv2ZbUSH8THmtoHxAnaMM_xjLi9R8_-8dACJAjnetSghM777BUVnH4SWbA22DEaSg1H4C6C1YQnmvYOGblwKrntNmwWf_C78NrKQP1R3r2I87Visg6QLb--S2SqtlMcrtPDPWHcCvK5Sxon_VbjNW9OaXjiTu9Hngxjr2-6EIJQCHS-_PbFK3SpmxZARbSy9sfgHM1-bghy1peHtRbV9XEO3LH2lw47fIhlSR-v-4IfE1vAELOfPmGIUf2vP3imSNpQN0hv-X2Vt9HhZgG3wQmO7llcxWesNpRzst3QqNi0DfEArz2hFDhYs1ykOv64jtOlQcu3BPmp2Bk5eJOO-1KPJ_M3V4_a08qaa9tbnadIEQk4267riWGoXYL1YPVekcb0PW2SGsHKU4ylTKAgOVxWnro9UEQjAxXaoTPkNnV25alAA6CpstxHhzvDshoHgmIbwFlLQnL5eBarsqRNO5AHYmHBaStVykmd8AgZ5BYgcHd_kzyhuHG5OmxxqUDeLmY7VkHBPgF-SsXQPQgjuERYXQPob1kmvS0ih8e92tnHNIlhaxFEwUPDDZEB2tJUCYSwVMA6jqfaZ5sh81KMMNV2i7m4Gq2ejoc7Ea8Bd_JAKy9YCikeHliiqB8QVPwGAa4Cvg5a4YIIun22_JH59OtaoGvtnwSl8RAHiSXAjlv7amnaeGEbpDRbY62lk_WgMq-_V3vMcUXyS0RLgZn5VmFpcJKDEsmnG6Jt3QpT1T48Ex1i36A_Hoq7DfMxurbZwsAQOnT8OWaFr34p_g5HohbFWg5tPUkCSB8YfXA0Z3c8JfeO_vj7m7qWPoAUQFm_82LMk7u7sJSWDcWl-DEq5Gs5HWX3wqVvZW47LCNDq5X8dDbtIQ451tdX7zwkkMQVSS3AGfFzVDHbvMlUlC9TbvQa1vAOnI1wnUjnzagovUFfnE0_jFL5F4L-QTMBQXd5iECE0jVQVgdDeZ82SsBQHbUESnAbFpg_LEeltFYyL42iJItcd19XFJunRkZb8OU4hOyqiixRQZ-DNPIL0QctciX_t-fzJq6u44MRD_k-fPJxcbDaNHgdLs0utuEXiqybV-dOVGVXNH6ZC7BGoIcoMpM_cp1VQihl4AgLtf3HqtL73zLs77jQn-X9UXu7CH8bne5x3BEsaOJTCO9zGlN6FjfuzAMflxsSMXbbHRDuLkrCGLOnhC0sF6YsLVdMtxbzwMl8rY-lRHCMvEFqJLF6m2tRapx3rYhc_tEAnF6r45fwgQNd6_N0Rvn4PYbmoQURT4DzmK4gXWItL2-ZAWxvZyDTCjyn1xmsIbe-AOSrg0eqz79gmtATzDlxVX74ik-3MHabLZHC89CQ0CbWLfrTLZkP8iTBKI9q20N2rlww5LuXIPC-7QzmjXAz9S85AEbC8Md3BZAa0W3f36QJwUTjTuJ6ewviBktZw3rcGXE1-3ajPogeQpuPA03ty-3nQl4CWSWsgATUA0oVipvGqvOc08Z0msvMbS3Q_NOtwbSawmNYLZzL-C_2Y7-VWkIt_qmTDD9_MlWlYd2ERnm0tvyFssGDHcYNjFlQx9_zdOxe6k7ioBs7ztgC3efSyRHC3yRtO8YGrAOwrLWmUU0VF8oNsCI44p357W2mcEbsiRrdVs641Nx4X7iDNa1zheid63-TSipfXTcsV2svTmA1AF53C2cp6Bfko2tCHQAo__4xsrOBxQnW-RMUvu8OMPCg4eM9i5GsZrpomKd8OGejQU8rDbSVRbdbd-EyeAkYCTCwMJitO0biv9UO53JvHZmD_ti5hhm4rU1ZU8-1P0m6lDFyAokKqpYjs6jLae7l6ctmw9Oa0M_9BTOpjw_V2vgPfiBcqq5JTJXgxq6I9hfDQN4LtROc8O9rhdFvlwyvOhy_5G1GTwXh3KNCME7Q8eZyCD8dthScqPkQnVzBfIDxgR7Hjsr2a5oGfgVBPCEa4AQoOWFO3DFfEy5BJ_OvVnADtluhADuIhgIiLhOtJJVWUtfdxETflhUpL0XC8ke8HzxZcu0iAeYu1ObPaXBSowxbAF7hq1aB-wSBuEGx4Nqt2nsPgmTE99uCIf3dr8zPOgce78QtJcbuTYgv-71VOifZWoC4ron5MPqpSjJT24WirzoNhEwR8ARpm01kHuPMu8itIbgPAD0CAwsLhRlAe24z775bTUzHsQxMcBH4dfVfnS0OU_wafJ5VuWc02QzAEmyIqrxsRiUFPAkLm6_3O70PqEIN_BDEuPBKvK93YIzwv85D7-zPDDfVoOYYMKZtRJgw3SDOiqS7w5XIV3zICFwwHbwBbP6_cVtA518twQGP1BgqF2uTAhZhe7B9pbg5na1kxQtZLmVZ5ItYD-lEAUESD7mmPZ_oRO6TXsn2dxu3uZLkZ5ha8G9xFRBFpJrdds1X-q0w9RzH9Iko8AN6O7GDsxdUWSQXgpDn2NB9rOI9nOdhnC_X544j8X3g592RhdP_SExoA23Jxrtv5WH29WJFrI9n6c1ofDN_0KusrUKiCGRQbplE9A9JelFbLo1dzbIACvMFbzugMQAu4AE9tciGvLpxlMP3HCgHRShKACpB8m2uL1Orsf3QNEGkU985ntbzGrqXpjLddmFWSbyd_5jwh1tWfy_fvaPedzXrngMQJAtKx6ujNjNFx4eU0Lrk_efYRnvQoGbujyCk275qW_sjCM_96x6GXQ0R9CnnwWm88j5J9zbFgFWwjlBpBoS5bS5Cy1zK8yR3xP08ATSOr9EzoCBTKdEN5R5AWEEWkhSslUjPbfigyxjeao0eFBy7gbc8OaJZf4hgXRbsj_8CM9zOIgRp8mDRMhlSwvjw0PtyXHh7lOvDd51R7YR8ymQGRtzIetWn8kk8Xz1EfJfdCBDcuO02TANYYTmcUk1uZHB4gA7UA-UKa5xsM48xXK5sy6jtjMfhoayIYudVmRtKzqtoPFjv7shppEG-ASpMbXMA75_LsgTbSwOOcqaDZr2gswHS_kkCrLhZUcfHiadxWXxP0h4BMhh15dddizIa4MD5MDu2WQnQ23usYY3wobMl0Gyb_9hOFxSX7jNVZJWfWUskDZY0xuqWjzY9JDzSI8AODEDV4tQxHJaKoaoEolxUbLLFv55cRnd_knWSye3Sxh-h0-B8hnpFAExWBMUzCbWgycI6cWf3Ia2dSMMEAq4vt0NTvBscvh8XxRjRpOt98feMLQaHartgrVkfcWO4HWrgix_zpIhv0l7aJ_mWRH3mdeeyBl_FhGEAmMHpAdJyYe8rNKbju7v9J5DquU5i9dmKNCZYIc5d9fvRUKxgJC2yvcUWzAAV48x4ksw87U1bxMiAP8AkheEDr8nbdSQ3_99fAbu2mQqp4y4yi54iHbIv5AsoDPf2U_CtZHFcqIHDp876aAZgcirSuZFf0LSRQ9Lsp4sKbbnHM_a6wkQbXtGuoOHUNGWe4t9d9HtLwPwIg7tU4flg0ckvifZZyDFLsOa_r0UdLA3x2amUC_yEF9KDkFXJUsYiLuHBZ42qgO05BJ8zzNhYO6J2yYrxXigDUViETrG-ngeP0Fnr3YgzccJ9-R_kPkDOg9Vtg4CTA3lyHFZXoOFosP5PzxY0pYVWekdqbAJC0gsz9Ggxu2oHOvIEY5nA0CFgtoCUj2bXuzWPgKcgvgKq7e0ZbdXeA4EY7BgXNHTF0uQBg8Nmcs1r6e_fANtAyu5-M9kzPzzvQiXea6rcm__Xh2F-A4M8TCEbcQEVAQTSe7wIMBT8KCpXNZP10elx521xz1Esmta35bd1LW7wOa_dnY1OriW37UQ646sgINP3XonEgBXcEvWa-EJFi5AzlIcbYRusyZJUE2PD5BWL_ex7Nz0qNUDd7FbWI2-KgPOJyBPo0ifF4CXHQd5PMrVOr6HOO1P6rf9VWBXsNPPPS8e3-PpsdOuc3ItFCrEZ51hyqhC-KyHdOByuM2ECI1VIKjPpXixfi9ZwclYaDcp4ffjAnAT6e71rUPw98rziaxjnZbYeRZvbNb6J6DpVhxiYEzUyx25KPKn0R7kzG7vw3-BJODILl4A_iUOkWYqn8M8UlbYnyLzQYwmj8nYQcYiNCvgkDuygVtGPCyPoMFexvQqzSvRDo7Z4eSQNuAYWezpu44r5MPaIxAyiwymX1bjlFzwBsgQz79aYPaCLU3fnmCFGKGi-RsWw25fkH-gHvhk4N0TQ6UQ-jdAbJdeIbwqwubniNRh9UPucVjF8PAvuu95URxFEY7rIl9G_unmsYM7uxH38jDMDoWIRlLz0Dysw5KeHoqwvsr6do9wZOuSJwJWHORB8byJ3-ix3OgudZlELCSr2D8Nc4JC8lD6I_oSW0O-7JuUn3th-9EI08duUrAaLUHuJueV42wworHCZWVskHfaq9jLCo1mU3rnSYeF2XVIaUD-hycnET7kP9kmXztYpCgs24kQeMpKoDZLP8N0MT3ES1RVu0XyWcQwIg-uj35EaoDWrx3oyfayG4pIMnQWP6RznRALts09sPpgrzDrDdnjv-JoV-2DYKlkHvBJkop6yFbVIUlDQo4gChDV8HN6mgiFoclRHs-foORJdign5DoCG4ggrURwu_W3nr7Wt7oPDwTgW1CB95LaHwQ2ksOXLtx29YPvMuhoEf4J885y4XKuAx4IRpwYLoN-TTG7vWOpIXregZWy9At5C9zG7SsDrXDYX6PEf7iAoKgFxUpsngyzXwjKAFxNqT2uSIzyLcB5SucLZXfWafcl9wOu4paBmwysbrNw1eAkl-3tjhW4pS3kE9vpql9LurhIC9Zhk8fDCKzz5UEhXvO9CsrNB7o67cXdx1c4uIfa2moMdVOWW6r91m086Stlx9mazf9kgoKc9nAjZAXnf_F7LjwenihEjINf03ot_A50HqhKj7hy-bDe_DR37Jt_kGDHsfDJZIO65Bopl0UEoI1syWS1S6mfAcyK0C5b_0Fo20Nc0PRaBOge9KyvzbnDArhbCPf0RA_cvHlqdhy5cAvuK9i764QBEjAaeb6lT2XujDwCG5LlSLBs1h-a8HigDqd0a_JYnSpuWXsePTsaICjv3umJPRktD6ZI_m2XwmPOMggRwi--5DwQyaOWq43RZpSCD8OgW7VJL8B7Ufh52Hmeiuc_CKRBfumXp4Fh6-1YSQm1jBuhmcgmU6YaESkex2I1ThPvTTomWsiYnhW7YXXFjcE8ztXubudmtkFBRLE5G_eWPPP7B_JRV1_Lf5n7BRL-42f_h7EADJWxn5dbwhdY76lYO80OaGNiYkJcUZFBF0IJoSGBLU8kQt8PS7sPEn1tg1abMN0hgwyCbefPb8NpKiO9cr_Hs3oZMlTqJlvZufrAAki3P78Nbm0l65lQHw_yE7q2c-AT7rkiS0geUAyo-E36h8GRiIqz9cfPUaJxeYyq-ZYOD3VaPo7ZCmkFt8AGD21ZnEWDEKVADmnbLih8CA9sXKRHv8sJsXFDxU2R2wOWGCsj64sEFYnCnDCr6_VN19yGh1OatbMTdz_6etRu93pGQGgE-EwT5EcPAheIIDSjeFjRHqgUIMA1_Zx1jwRejtw3UXR51DpAdiHQuVo5Jvl1917EmJfHgJxBOhEAq3fPvtl1ksCzAsAN4vnRiYubGVAd7hCeQoYijkg4lQx8g0jZEwdPthnZzmBnlVxcG9RY-UFeApAhF2hDMtEc0OVgv1BD2jW1G9SA9JZ984bDUG6c6VWfexO2lHksEwrnqREPXrc1I4CHpd605iycPiwJ-cFjoopuEnAIl8WTQ9Z03AQiTpmd29BwV_xuWu44vUVSzFEcIkrgt-SJKffUQC9nkt7WeyDYBgKPC4dkHYN-7ClGh1vEaD_OUNbx4K5MSIhIhKC9eRmFTuzDunGwoDIHOfVVJAgUMdsoBtEg7VkG94itiJb62pImCyTbgYflkDasOTtPpQT_WSbfeHzsfDy_aK3Wvg885fUMJUECFYCsBLdbp6egali9y5cFsQBxRaF4oj33q7cTlcqaOwLyRt5BQDwhFe12Bwkn4eGAigpzAZsb7qwTVrdirOjyqK_kXgncxik2qCBP7Nm2a3_t4QmD1xOf3PUpJWUlUWITagihhtjBWh0rcj9KRQhpVW49wdMsHiH3zLMHlWDn1Z32GFbsP81zdSIMsGMHXCTVNLSBUyVwtetGHUx4Lrd5DlEINYO884x5lLFVeR9eGGyXhpnCoDuOCbCfuJ7N1dF97mFp9wHF78vZNTk4NeFJxYOx-E9s8mueXk4dBjjX8W6WGlzIHkxJ83qcVsOS4r_EAk7Ig2ryYPKG-u1M5_oOtOS9jkanDCJ4QOiF-VwgSiTlkhoe-CDkTdFwWyptEY1bfm6BZIxEc8wbjsNiZDPndduXhWfrm1ZybcM73MEmfhIJwRE897r66HrUA85Q3WN38_GwMsXF8TfAYiWaUeCrA-bg2cNU8-URXcByJFts-YLrRtEdnYBoKm0-IXveyI0NlD40KvAQIVmsFStXLucKoPizh0h6cw0dhzT4BAsVQ8YKGeNho6mBl-ngg2HnL8-sVd9hf7lHOz0cPkGN8wQZeoJ0nwttSRfTujJZ-4So2mDfLO1xreP0BHc8PbFmWwN4BVyhCIZ7jelo8hQWxM4QMGX0NhGkXn-4ydlkLYH39gTWata0qghOkskdHtQrkQwbhWzpXKiK610-iZfbqAdHgMraEGCr2okKfPqR1zw2cvzN5fdsk3cFBYZzqGHZr4cEkgfVWJXzhcLWHNchxLi2r1DKBV-TFfDd9nyuE5Z2hhfBMlogYGlXHJkFD_cBosMBDxLkT7-W06jgJzjYZRPNYXcxIKvUYpHWjpaTS8BC2-nwYBbU40mevnrfaP8YwQrReAUPJ3ffNmM65GmuhojHbTdoABp2yc6lmE281ZNC9sy6V1dZ39VG5OQOd4U78A2ssZAg-WkVxnSXk-NokomRLMRzdWoI0tshOq8c-KoF2HTv5yFMIjzk7bBC1nDwZ8l6wXvixNLXmadTdMao-VLNDkfYgDTSVf4FEk49StTgR2umg4nTuRCggrftYFePUwdPcIG9EOxk35htWO5oJgRkgtlHgOawdYJVvQpy1IzVnM6CXJFjn15-caLTsdqV82VIOi3qslWmt-bBHz5sypAhD-51RCN_ksFgNhU_hwxelzsQ0SKI5QoYBWwURgVJwN9Oq3d8omAagx06UCUSH1nOs3ZJTUrWAkTtpffsUl19ZMlJNhHiY39c9eC_swwsOntxPr8T8nmZp23iaRlSb2PcAepF2zOgHd4O-BlkVx5IWBOk4gN4k2wAqOHrhSISxYam5vyPBM2094KwHGobT09YFiaxlNW1ZPc07I-Pm3BdYoMn87o7QIRkx5c8SFoozhoA1528cEb-GyQ1eWAPFo7Wcv6IAx8ct9GsRVujg-chUmHr8OnmHJ_iSUFu4FoN57G6U-QZaRtXLrlE8_-c1T1j3-ADQiy4XjyxFnIHIgnnlWR5KAvB7nYmaeSxGQoSFOzarxAuWNnwIOvrEI80eSp-TSFGW_FahoECZMv4Ouywea4ZZKqgSJIPB6fhpOwZCTzdQ3l3Z40JzbkGggQSE4_Irr7T-RZuWLfTx0pOsQDH1fe0Yu7qULdgzzHxDKW63SNMNqRx4x6HObubzWPNtin_u1oxPOzZV8ZZZyy6Q-Ae89hr0EOe7DK6bRYETyxNIRWIJMB_eD23KdwqNsESbUjD7R_3jUJyKMm0RwxHuyNYgs4tTqMgDpo0jRsjf1nvfU7HcHkQnqBh3YNnSKCeaKVc550IS8LeTZhhycaRt57RGFXcWfuAD4TxZ_RL8citc7bsfEXgj1U-JSD5DtTILG-3yiaXHpYDkOs2F4x_zIECP__jZ_-Y4LFdQsYivt2nhDVfGg1MEs9qD8o4IjHeHQ84TxMjD9ImJx45SuwKoCAUivAUeeuxfJW0yafl3B2-Mc0vuCS0KKGfTYHr30ZHZzov4BSPC1gKnznWmANSaEeC2mxUwGF7xNrpLLFnzeVzbN5zHsP-TNLTdB5ItgzmILJ1thct7uEBD0LYWGF839JL-5hgZjabcr92bxe0LJ8gVf3nmi_bz9ZleOz-qNByjy2N9nOXRwn_x9UXGSVBbJdy4Rk5sw5uwh89PY91C7awQMjXBJTmwR_BDDyHO92jrhWyJdkZJ2trbvVOOLGY_L8uaN3WuvoDsAT5HEZXCcH1b1lfgtmbuWAHtjyKMOSYrj_4c6fCVQtYqDMQrkw3PAiUOyBxpWLn4b7CJVlb9R2b_q9cHXxshRDWm6USAh3Jev4sNtLjsf-4OjgMX-H-ydrw9xFzuRDDCYkJh8topxYcM-mdxIZwcNcAMmVY2wTCI07dRqfGmrkf-Y7bFAgdKAmB4BF5EBlsa-vIk5PgkEceoVnNPCcqs639uQdBlJGyab3TFcLcXRL-1Kl9nrNxiAeeA71CY1gbcXAV9BeN9nNg5YrgiOMrPMta8BrPMUP_Jm5gAwEUjOeJj9lMDpc47h8aQugneLDj1-rtbBSE7mMAG2KOIEmOV0v8FFbKV3lmPS0Vxuo2Jxo4hgau70A5cqdztwpP_LkzWosc8ZhGLrMb9AzBfPs6GTAb6t6O6YlEFIijOs7D_11nlMjroJiH4YKnIIFwFt9t3kV6m0Mv3uYuZLKZyxmQJPzhQCG9Z7R2EgR4x2uZ2vkvtRXY4mrh5zZtt5NipY7y8iSqp9buCS6kaCN9dQ_Gs9EyGV863KBNgMqwi_QQfw6EBQAM0ZDcWpWFQrzDBqlhGftNTsCDR67e7EIKzPFu2eNcFaL-HtYpn3iFw10Feyjt3ng85oWghwLL6SaEjQBh_TxpVxJOXK1fvzcYPrNiJzsmBFTog6ycmxuKE3qI0gHxyZ8QJtQta2wHSSA_EGw4m18kfYx9dYbY-yD74Mkny-fONHL244KHFatwHyKfBAqHeNzfAQnXly_MacnXKKJo7_VbT0CR21nx0_Z5PHOd9b0BEvJsiLbZOMAJgfta933sKTurDR72bUp7YX5puDPPE7-sjxJloCcp5vJ0BGt0ScXxNFQMkt12z9ZsJrOnyvHkh1v5B_782n7UACSkhGc2W_Nc_-zFYWOIy0yumVZdPG6cnZr2jrqaQVNw_42ci-xAH3X4PbkxIk-kqECso5Qc2Xlzoe5a1rAu2mZ9N1u6g33GWoj1fG1hIKOaEBxUqB608Ic2sKnqcQhCdKjsetIHTAj2J84i0571fHF0vt0yA2oESsA_VUIEO2HCWyVhJGgS5PPO5MCVCe_gMmy_dn6Xp-bg2PFncNbpm0EieNqq3WenAwpfIi3JTjxi6ISi5ogBT3Da7o5qd9raeoK9cVmkVccP8PzXQEG3p3uvNjf-dGiis0jkLxwLnjbqerOHp3PjMaNVWOil3eC3bbwsxbm28Anh1zlBL1THsYtqQshyXIPLcDKnc1zZ1m_A0Yk4YIGz8PAvTwb3oJp-PLbKg1CQe1DQojbBZKu9k9EuN2E977bms_LNyQlFI9rQN5wSYMUEv4OnOzG3II1jlcI0MJxE62Tn215iOzCH5049VPzIrsABwuvBUQG3_jgJrnvic7bJXYVb5Zscq2s_gNNyD7f73Zq1Nm4TqOe7EqD8Wqt28gcw2myXdXj6rJfZBsZNYuGTLU4SEjhpm_VnVA4y2dZwFoUIWW-If5GRnaf6sB7NaefV_ryjGGr9dOhVriQCksEaQwTCPAAhKcFzJAWS7CsMSDAO70KErX43_hBfi84nUyN7mjB7ssexPHcHnOG9rUMIH9T-BQ0nAqezo1pdhwg8a43nvM4fIG-QDp2v01-ygF2ph2Wh1t0pfWUD1nnhBuiBC45u94gFycOy9ACVb6gGVydZ4jLAWE_FX77RtOrEowHkeuxiArdNBVbKHTnUQgn2zV0OGngdA0fMVYcXHS6K7xXwqEuda5pvvS4ymEUGN0BxmHb5lZcB7sGaAOdeYwUdhGW3LUmEMLSprrqH1myfHnaikrf4slet8ArXkeuB1gdPBZwPapFPsJ-mOhqPDOLuNS41uuOh7a0HYvxk5z_wxx4pgbzZCOjkSJILFK_A4JNbz1DZdNl2hK6-V7uw41wQU7PM9Z-I6nx0OZBVumK_LZTZeqbv-XGf_nW215SZc_053XjUtEfuQT-BmdXiV9NvnfuDx3XPPg9I4RpU5qzZxMeSz8lAp5B2SMehbuvQy-tBc89w2rZ6jcORIYQy1IIQQVfZ6z3RTS_Cx9lqwIaHO3m2T-ahiUh18uBjdZSanSxXXkVgS23kdQeInsGez9FiOoftQmGg7Uwwb0HFTVC1cUEOEoY0kUmmRxcIM-dPkk0rcJectIODr6ob3OXxqItM27M9fLBiDnSwJbI6znk6N9Bz6jAbhMF9N7mRE1IcXVmBan3C4dCS7_SP8RRq_I-f_WMOrsaOwdPjlx4JacEJHkiS6owZxKWHZu0PdeLU_ThbDShpDt04bcSCYwwP1sgqhvtqNUXUGanf38LFX_fBAakZ3KeBMVmwB1U8Pfg6zhN1cP38lvzuCS-C2slScQ0LdL8FHWh-g0iP4jxat0Gux_PNfXhexoNpgZg_nKW2PrQ_iFH4HrfidtMDKSkTBfu89gA6FdZa8I0EN3-ebn1b9Ua-TY-Qe6Yw2JQE70Rn2nGbbGN1I9P5eGSh5mH8dQ4SxRB6Pz1R5CiglLKbL9ls6t5LJlTCmvp6OCM-Zme8Wuy3Z8qTLm5uNpSLdRTyJqy2QJHRw9Wmxf545r9Od2bvNcWHxcseDLd94j7tcCnObNM5GpQ9H5d9xEAiTn_bt3k49yM5MLTCKZX3LEQkM03H_pYMcsDq0UwFSLVZTk84SHDTDb542jRmWdvtENPrjeN6UPp0JmBwPm12r-Wxa6BWD-dBwACz6MRX2xDgvR5kh6w_Hm635wj4JPngRZOks2aCsIKeDnO7ZvFA6_SPDTD19nXCYx19wJeytS13DkEw94SG-3L5JgRsM4rZdgBPIkKHYeBQkRnAiOxEJZWnUwCJQnJ6sf0VtJ8W1jxJJ7-GwJPiHSx8OieTJ-wLlnFWt5RP_v8Q9Q4CX9cDURzhYcPl2ttETCJLPOO7ytPdzWb71R03CY8J-W241uXecnPf6Zz2FpMhHPL2c_1HVrQ60AnJ7c7qfT2J9ELQFdgqLI1n1gAueRbRMh6FTFnn898Cwp8eVymdROnwd-cJkeGre2FOT1JFRfsfXo_botfLOnTYc3mL-4xwx-x585svLM90d9RzBEp-Z8xct0MVotw7JWfap_ra8ELawM1gy4lHT3w7kwzi43wAJQLueaRUJdyVvOUAvWdtYtyXuvgSykl2qBdTWvSNBg0t6oAmOG9-uO-1E-PsfRTU6uKGLTn6xum2bl2dTpjP6Wyyd0C-OFN7CamEaL1tkV-_dfY5grcRSp5KO9dxHh6OnSrOl8OZk4Pn129vB-4PB0GvDwi-wSGS3OI0A8zV00DCyevLX1Oqwz0uZ33auyaaHTw2BdrhrCePcJ03zmFj4vR0vztbP2_CcHaE5bH7rdbCpifp7e4jytZF4mnpAEbQqe-jznUAytP5-3bEeNmzsIoe66p8IVeERTfIsA3qii9uyCGRzoi1q1kxEOBHjiRBpYBP9gfet9NsbqtwSo7rhESSwC9H5jjrYkRPuWa7XxyfCZPw6Oqx3qdxuIdtjwtSyB2w15dOmbBO99rdyTW6zwNNYOPTZZl-vPYw3ITjvWAOvuuIHgd2d0l1nEQ-0OpQ2svxSPPls9s6pHGvp-XgpHA4JS977tkbP2wPxp0L69QQpwS0mHUjntf8ak_QPoOwymuqV3biLFmjurlBzkGvCWoepeyrweoHvUm6pS2M5R-QcY5iDRO4WJ6Y0RWXL9n4QYHivC15Dfq0Pe6ku1M4bHTBp7h9N68ux7meFUSdgI4dqgVo4FPhlIQ3uq1ZqCkEA77hvjsKqsoSyIASu3Q7HpuIgx1U55XYKme3SfYIEASkpVW6e7qbmOAp5M8Ci0eDi9WMZIyaWcm_DnLy_HV3qpKvS46O3UeidGjPY05wfGKzNlUuFCLMFjl3kw4gorC3d5aX5bZQz4oh8Y7DgY6H5WD3JipZ3IHJBTZrq2C12c1mQLs00nr_K0ifoQ8F4lXNLRA9j7z53sqxJoyDyebIKTl73Ohzvj333W2vKEjx4HzSy6mEzv123_ZwK3WNd6srf5DaEEHgKJHiabXlhJdvVenOpnuHM6edxmsnlrO7PGDqzNbiIIcjOddGTYd4heU2hwnqsE6EcYsb_hecnXD5EoDI9Yc1GAE8AX-K22zn6-spVHKIPWfGHW5mvLDNyy51TzV4dC47XLTILqJ8o7g1-BIS8XWstG8uJeQsLTgV1n5dFVRzGCw4DBkizwNevi3y8UVrJ0vblcEZmjUWwDrPy1ofPApK6f7G4SkMmAm0sPoOHE-VdKLK6aTmheipn-Q7RKpDwpoKj7yYbzJnyYAwLKBEt9leC_MRTenYbZaCpJ0CIsItKcvJi08S3TPgq06PcBJ9NDt151qMd_iFbh3w-Ct53JOiTiKRBJ_dA4-ssYNAo1sRxI1nUR1Bi2-TNdyQsrHZ0XfEmbgBoh08KIerXoXlr_rc6-4fnLUGvqifyTfRFqKlOFE2JWvZL-j7WBhKc-lF8B5R-1Nmh0B08oIN7Phu8d0xZEzHLTnGwrDJHlQySTjUGRiK4Bku07Oz8LjJhvP7Gh1QyYndpCxcC7XX1ALT0ddv94BJ9hiEGho1wLVXllwkLROW4HtyTlgpwePUJMfpIHWC5xOqEwVu--6776ohY3q6VRLH1QVSA98Cn4E-OALT47QW6aDYoBUPCu1lM3S3yoGMAsqqY_ysrnoWHJ6UnB7DY-Rpgxgyc8LX_hq7r981UsBpkvy_QYZYJLN4hMcKviNgmyzgdretOc_BfrHHLp_CQ0wjE79v8ZUCxIhjNx8P8APW0eGl_2V8p0v7j5_9Y_4Xqdo7gQ==";

void SongTest::initTestCase()
{
    Echonest::Config::instance()->setAPIKey( "JGJCRKWLXLBZIFAZB" );
}


void SongTest::testSearch1()
{
    Echonest::Song::SearchParams params;
    params.append( Echonest::Song::SearchParamData( Echonest::Song::Artist, QLatin1String("Modest Mouse") ) );
    params.append( Echonest::Song::SearchParamData( Echonest::Song::Title, QLatin1String("Float On") ) );
    params.append( Echonest::Song::SearchParamData( Echonest::Song::Results, 2 ) );

    QNetworkReply* reply = Echonest::Song::search( params, Echonest::SongInformation( Echonest::SongInformation::ArtistHotttnesss  | Echonest::SongInformation::ArtistLocation | Echonest::SongInformation::ArtistFamiliarity ) );
    qDebug() << "Test search:" << reply->url().toString();
    QEventLoop loop;
    loop.connect( reply, SIGNAL(finished()), SLOT(quit()) );
    loop.exec();

    QVector< Echonest::Song > songs = Echonest::Song::parseSearch( reply );
    qDebug() << songs << songs.size();
    QVERIFY( !songs.isEmpty() );
    for(int i = 0; i < songs.size(); i++) {
        Echonest::Song song = songs.value(i);
        QLatin1String title = QLatin1String( "float on" );
        QCOMPARE( song.title().toLower(), title );
        QCOMPARE( song.artistName().toLower(), QLatin1String( "modest mouse" ) );
        QVERIFY( !song.artistLocation().location.isEmpty() );
        QCOMPARE( song.hotttnesss(), -1. );
        qDebug() << song.hotttnesss() << song.artistHotttnesss() << song.artistFamiliarity() << song.artistLocation();

        // now fetch some more info and make sure everything is still sane
        QNetworkReply* moreInfo = song.fetchInformation( Echonest::SongInformation( Echonest::SongInformation::Hotttnesss ) );
        QEventLoop loop;
        loop.connect( moreInfo, SIGNAL(finished()), SLOT(quit()) );
        loop.exec();
        song.parseInformation( moreInfo );

        QCOMPARE( song.title().toLower(), title );
        QCOMPARE( song.artistName().toLower(), QLatin1String( "modest mouse" ) );
        QVERIFY( !song.artistLocation().location.isEmpty() );
        // make sure we got the new info
        QVERIFY( song.hotttnesss() != -1 );

    }

    params.clear();
    params.append( Echonest::Song::SearchParamData( Echonest::Song::Artist, QLatin1String("The Tallest Man On Earth") ) );
    params.append( Echonest::Song::SearchParamData( Echonest::Song::Title, QLatin1String("The King of Spain") ) );
    params.append( Echonest::Song::SearchParamData( Echonest::Song::Results, 3 ) );

    Echonest::SongInformation info( Echonest::SongInformation( Echonest::SongInformation::AudioSummaryInformation | Echonest::SongInformation::Tracks | Echonest::SongInformation::Hotttnesss ) );
    info.setIdSpaces( QStringList() << QLatin1String( "musicbrainz" ) << QLatin1String( "7digital" ) << QLatin1String( "playme" ) );
    reply = Echonest::Song::search( params, info);
    qDebug() << "QUERY:" << reply->url().toString();
    loop.connect( reply, SIGNAL(finished()), SLOT(quit()) );
    loop.exec();

    songs = Echonest::Song::parseSearch( reply );
    qDebug() << songs << songs.size();
    foreach( const Echonest::Song& song, songs ) {
//         qDebug() << "SONG  TRACKS:" << song.tracks();
        foreach( const Echonest::Track& track, song.tracks() ) {
//             qDebug() << track.catalog() << track.foreignId();
            QVERIFY( !track.catalog().isEmpty() );
            QVERIFY( !track.foreignId().isEmpty() );
        }
    }
    QVERIFY( songs.size() > 0 );
    QVERIFY( songs[ 0 ].audioSummary().danceability() > 0 );
    QVERIFY( songs[ 0 ].audioSummary().energy() > 0 );
    QVERIFY( songs[ 0 ].audioSummary().acousticness() > 0 );
    QVERIFY( songs[ 0 ].audioSummary().speechiness() > 0 );
    QVERIFY( songs[ 0 ].audioSummary().liveness() > 0 );


}

void SongTest::testSearch2()
{
    Echonest::Song::SearchParams params;
    params.append( Echonest::Song::SearchParamData( Echonest::Song::Description, QLatin1String("emo") ) );
    params.append( Echonest::Song::SearchParamData( Echonest::Song::ArtistStartYearAfter, 1990 ) );
    params.append( Echonest::Song::SearchParamData( Echonest::Song::ArtistStartYearBefore, 2000 ) );
    params.append( Echonest::Song::SearchParamData( Echonest::Song::Results, 2 ) );

    QNetworkReply* reply = Echonest::Song::search( params, Echonest::SongInformation( Echonest::SongInformation::ArtistHotttnesss  |
                                                                                      Echonest::SongInformation::ArtistLocation |
                                                                                      Echonest::SongInformation::ArtistFamiliarity ) );
    qDebug() << "Test search:" << reply->url().toString();
    QEventLoop loop;
    loop.connect( reply, SIGNAL(finished()), SLOT(quit()) );
    loop.exec();

    QVector< Echonest::Song > songs = Echonest::Song::parseSearch( reply );
    qDebug() << songs << songs.size();
    QVERIFY( !songs.isEmpty() );
}

void SongTest::testSearch3()
{
    Echonest::Song::SearchParams params;
    params.append( Echonest::Song::SearchParamData( Echonest::Song::Description, QLatin1String("psychedelic") ) );
    params.append( Echonest::Song::SearchParamData( Echonest::Song::Results, 3 ) );
    params.append( Echonest::Song::SearchParamData( Echonest::Song::MinAcousticness, 0.1 ) );
    params.append( Echonest::Song::SearchParamData( Echonest::Song::MaxAcousticness, 0.7 ) );
    params.append( Echonest::Song::SearchParamData( Echonest::Song::MaxSpeechiness, 0.4 ) );
    params.append( Echonest::Song::SearchParamData( Echonest::Song::MinLiveness, 0.4 ) );
    params.append( Echonest::Song::SearchParamData( Echonest::Song::MinValence, 0.3 ) );
    params.append( Echonest::Song::SearchParamData( Echonest::Song::MaxValence, 0.9 ) );

    QNetworkReply* reply = Echonest::Song::search( params, Echonest::SongInformation( Echonest::SongInformation::ArtistHotttnesss  |
                                                                                      Echonest::SongInformation::ArtistLocation |
                                                                                      Echonest::SongInformation::ArtistFamiliarity |
                                                                                      Echonest::SongInformation::AudioSummaryInformation ) );
    qDebug() << "Test search:" << reply->url().toString();
    QEventLoop loop;
    loop.connect( reply, SIGNAL(finished()), SLOT(quit()) );
    loop.exec();

    QVector< Echonest::Song > songs = Echonest::Song::parseSearch( reply );
    qDebug() << songs << songs.size();
    QVERIFY( !songs.isEmpty() );
    QVERIFY( songs[ 0 ].audioSummary().acousticness() >= 0.1 );
    QVERIFY( songs[ 0 ].audioSummary().acousticness() <= 0.7 );
    QVERIFY( songs[ 0 ].audioSummary().speechiness() <= 0.4 );
    QVERIFY( songs[ 0 ].audioSummary().liveness() >= 0.4 );
    QVERIFY( songs[ 0 ].audioSummary().valence() >= 0.3 );
    QVERIFY( songs[ 0 ].audioSummary().valence() <= 0.9 );

    QVERIFY( songs[ 1 ].audioSummary().acousticness() >= 0.1 );
    QVERIFY( songs[ 1 ].audioSummary().acousticness() <= 0.7 );
    QVERIFY( songs[ 1 ].audioSummary().speechiness() <= 0.4 );
    QVERIFY( songs[ 1 ].audioSummary().liveness() >= 0.4 );
    QVERIFY( songs[ 1 ].audioSummary().valence() >= 0.3 );
    QVERIFY( songs[ 1 ].audioSummary().valence() <= 0.9 );
}

void SongTest::testProfile()
{
    Echonest::Song song;
    song.setId( "SOYMZLR127CF8DD122" );

    QNetworkReply* reply = song.fetchInformation( Echonest::SongInformation( Echonest::SongInformation::ArtistHotttnesss | Echonest::SongInformation::ArtistLocation ) );
    QEventLoop loop;
    loop.connect( reply, SIGNAL(finished()), SLOT(quit()) );
    loop.exec();
    song.parseInformation( reply );

    qDebug() << song << song.artistHotttnesss() << song.artistLocation() << song.artistId() << song.artistName();
}

void SongTest::testIdentify()
{
    Echonest::Song::IdentifyParams params;
    params.append( Echonest::Song::IdentifyParamData( Echonest::Song::Code, code ) );
//     params.append( Echonest::Song::IdentifyParamData( Echonest::Song::IdentifyArtist, QLatin1String( "Pink Floyd" ) ) );

    QNetworkReply* reply = Echonest::Song::identify( params );

    qDebug() << "Identifying:" << reply->url().toString();
    QEventLoop loop;
    loop.connect( reply, SIGNAL(finished()), SLOT(quit()) );
    loop.exec();
    Echonest::SongList songs = Echonest::Song::parseIdentify( reply );

    qDebug() << "Identified:" << songs;
    QVERIFY( songs.size() > 0 );
    QCOMPARE( songs.first().artistName(), QLatin1String( "Bon Iver" ) );
    QCOMPARE( songs.first().artistId(), QByteArray( "ARKDTAM1187FB54026" ) );
    QCOMPARE( songs.first().title(), QLatin1String( "Flume" ) );
    QCOMPARE( songs.first().id(), QByteArray( "SOJEVHC12A8C13C3E5" ) );
}

void SongTest::testIdentifyWithData()
{
    Echonest::Song::IdentifyParams params;
    params.append( Echonest::Song::IdentifyParamData( Echonest::Song::Code, code ) );

    QNetworkReply* reply = Echonest::Song::identify( params, Echonest::SongInformation( Echonest::SongInformation::ArtistHotttnesss  | Echonest::SongInformation::ArtistLocation | Echonest::SongInformation::ArtistFamiliarity ) );

//     qDebug() << "Identifying:" << reply->url().toString();
    QEventLoop loop;
    loop.connect( reply, SIGNAL(finished()), SLOT(quit()) );
    loop.exec();
    Echonest::SongList songs = Echonest::Song::parseIdentify( reply );

    qDebug() << "Identified:" << songs;
    QVERIFY( songs.size() > 0 );
    QCOMPARE( songs.first().artistName(), QLatin1String( "Bon Iver" ) );
    QCOMPARE( songs.first().artistId(), QByteArray( "ARKDTAM1187FB54026" ) );
    QCOMPARE( songs.first().title(), QLatin1String( "Flume" ) );
    QCOMPARE( songs.first().id(), QByteArray( "SOJEVHC12A8C13C3E5" ) );

}


void SongTest::testSearchSongType()
{
    Echonest::Song::SearchParams params;
    params.append( Echonest::Song::SearchParamData( Echonest::Song::SongType, QLatin1String("christmas") ) );
    params.append( Echonest::Song::SearchParamData( Echonest::Song::SongType, QLatin1String("acoustic") ) );
    params.append( Echonest::Song::SearchParamData( Echonest::Song::Results, 30 ) );

    QNetworkReply* reply = Echonest::Song::search( params, Echonest::SongInformation( Echonest::SongInformation::ArtistHotttnesss  | Echonest::SongInformation::ArtistLocation | Echonest::SongInformation::ArtistFamiliarity | Echonest::SongInformation::SongType ) );

    qDebug() << "Test search:" << reply->url().toString();
    QEventLoop loop;
    loop.connect( reply, SIGNAL(finished()), SLOT(quit()) );
    loop.exec();

    QVector< Echonest::Song > songs = Echonest::Song::parseSearch( reply );
    qDebug() << songs << songs.size();
    foreach( const Echonest::Song& s, songs) {
      QVERIFY( s.songTypes().size() > 0 );
      QVERIFY( s.songTypes().contains( QLatin1String("christmas" ) ) );
      QVERIFY( s.songTypes().contains( QLatin1String("acoustic" ) ) );
    }
}

QTEST_MAIN(SongTest)

#include "SongTest.moc"
