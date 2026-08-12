.section .rodata
.balign 4, 0

@ Need tools/preproc
@ preproc: treat "label::" as ".global label ; label:"

gTerminateCharCode::
    .byte 0xFF
    .balign 4, 0

# strN = 0x08372aa0 + StringOfsTable[N]
StringOfsTable:: @ StringOfsTable
    .2byte (Str_0000-gStringData), (Str_0002-gStringData), (Str_000C-gStringData), (Str_0010-gStringData), (Str_0013-gStringData), (Str_0016-gStringData), (Str_0018-gStringData), (Str_001A-gStringData)
    .2byte (Str_001C-gStringData), (Str_001E-gStringData), (Str_0020-gStringData), (Str_02B5-gStringData), (Str_02C0-gStringData), (Str_02C0-gStringData), (Str_02C0-gStringData), (Str_02C0-gStringData)
    .2byte (Str_02C0-gStringData), (Str_02C0-gStringData), (Str_02C0-gStringData), (Str_02C0-gStringData), (Str_02C0-gStringData), (Str_02C0-gStringData), (Str_02C0-gStringData), (Str_02C0-gStringData)
    .2byte (Str_02C0-gStringData), (Str_02C0-gStringData), (Str_02C0-gStringData), (Str_02C0-gStringData), (Str_02C0-gStringData), (Str_02C0-gStringData), (Str_02C0-gStringData), (Str_02C2-gStringData)
    .2byte (Str_02C4-gStringData), (Str_02C6-gStringData), (Str_02C8-gStringData), (Str_02CA-gStringData), (Str_02CC-gStringData), (Str_02CE-gStringData), (Str_02D0-gStringData), (Str_02D2-gStringData)
    .2byte (Str_02D4-gStringData), (Str_02D9-gStringData), (Str_02DE-gStringData), (Str_02E3-gStringData), (Str_02E8-gStringData), (Str_02ED-gStringData), (Str_02F2-gStringData), (Str_02F7-gStringData)
    .2byte (Str_0302-gStringData), (Str_030F-gStringData), (Str_031E-gStringData), (Str_0329-gStringData), (Str_0332-gStringData), (Str_033A-gStringData), (Str_0344-gStringData), (Str_034D-gStringData)
    .2byte (Str_035A-gStringData), (Str_0361-gStringData), (Str_036A-gStringData), (Str_036F-gStringData), (Str_037B-gStringData), (Str_0386-gStringData), (Str_0392-gStringData), (Str_0392-gStringData)
    .2byte (Str_03CD-gStringData), (Str_040A-gStringData), (Str_0439-gStringData), (Str_046D-gStringData), (Str_04AD-gStringData), (Str_04E1-gStringData), (Str_051E-gStringData), (Str_0551-gStringData)
    .2byte (Str_0583-gStringData), (Str_05B2-gStringData), (Str_05EC-gStringData), (Str_061F-gStringData), (Str_0637-gStringData), (Str_0637-gStringData), (Str_0637-gStringData), (Str_0637-gStringData)
    .2byte (Str_0637-gStringData), (Str_0637-gStringData), (Str_0637-gStringData), (Str_0637-gStringData), (Str_0637-gStringData), (Str_0637-gStringData), (Str_0637-gStringData), (Str_0637-gStringData)
    .2byte (Str_0637-gStringData), (Str_0637-gStringData), (Str_0637-gStringData), (Str_0637-gStringData), (Str_0637-gStringData), (Str_0637-gStringData), (Str_0637-gStringData), (Str_0637-gStringData)
    .2byte (Str_0637-gStringData), (Str_0637-gStringData), (Str_0637-gStringData), (Str_0637-gStringData), (Str_0637-gStringData), (Str_063D-gStringData), (Str_0642-gStringData), (Str_0647-gStringData)
    .2byte (Str_064C-gStringData), (Str_0651-gStringData), (Str_0656-gStringData), (Str_065B-gStringData), (Str_065F-gStringData), (Str_0663-gStringData), (Str_0668-gStringData), (Str_066C-gStringData)
    .2byte (Str_0670-gStringData), (Str_0675-gStringData), (Str_0679-gStringData), (Str_067D-gStringData), (Str_0682-gStringData), (Str_0686-gStringData), (Str_068B-gStringData), (Str_0691-gStringData)
    .2byte (Str_0696-gStringData), (Str_069B-gStringData), (Str_06A0-gStringData), (Str_06A5-gStringData), (Str_06AA-gStringData), (Str_06AF-gStringData), (Str_06B4-gStringData), (Str_06B9-gStringData)
    .2byte (Str_06BE-gStringData), (Str_06C3-gStringData), (Str_06C7-gStringData), (Str_06CC-gStringData), (Str_06D1-gStringData), (Str_06D7-gStringData), (Str_06DD-gStringData), (Str_06E2-gStringData)
    .2byte (Str_06E7-gStringData), (Str_06ED-gStringData), (Str_06F3-gStringData), (Str_06F8-gStringData), (Str_06FD-gStringData), (Str_0702-gStringData), (Str_0708-gStringData), (Str_070D-gStringData)
    .2byte (Str_0712-gStringData), (Str_0718-gStringData), (Str_071D-gStringData), (Str_0722-gStringData), (Str_0727-gStringData), (Str_072D-gStringData), (Str_0733-gStringData), (Str_0739-gStringData)
    .2byte (Str_073F-gStringData), (Str_0744-gStringData), (Str_074A-gStringData), (Str_0750-gStringData), (Str_0756-gStringData), (Str_075C-gStringData), (Str_0762-gStringData), (Str_0768-gStringData)
    .2byte (Str_076E-gStringData), (Str_0774-gStringData), (Str_077A-gStringData), (Str_0780-gStringData), (Str_0786-gStringData), (Str_078C-gStringData), (Str_0792-gStringData), (Str_0798-gStringData)
    .2byte (Str_079E-gStringData), (Str_07A4-gStringData), (Str_07A9-gStringData), (Str_07AE-gStringData), (Str_07B4-gStringData), (Str_07B9-gStringData), (Str_07BE-gStringData), (Str_07C1-gStringData)
    .2byte (Str_07D0-gStringData), (Str_07DF-gStringData), (Str_0802-gStringData), (Str_081C-gStringData), (Str_083B-gStringData), (Str_0852-gStringData), (Str_086B-gStringData), (Str_0898-gStringData)
    .2byte (Str_08C6-gStringData), (Str_08D7-gStringData), (Str_08EF-gStringData), (Str_0907-gStringData), (Str_0914-gStringData), (Str_0931-gStringData), (Str_0950-gStringData), (Str_0970-gStringData)
    .2byte (Str_098F-gStringData), (Str_09A7-gStringData), (Str_09BF-gStringData), (Str_09C2-gStringData), (Str_09DE-gStringData), (Str_09FA-gStringData), (Str_0A07-gStringData), (Str_0A19-gStringData)
    .2byte (Str_0A29-gStringData), (Str_0A4A-gStringData), (Str_0A6B-gStringData), (Str_0A8C-gStringData), (Str_0AB0-gStringData), (Str_0ACE-gStringData), (Str_0AEA-gStringData), (Str_0B08-gStringData)
    .2byte (Str_0B26-gStringData), (Str_0B48-gStringData), (Str_0B6A-gStringData), (Str_0B8D-gStringData), (Str_0BA9-gStringData), (Str_0BC9-gStringData), (Str_0BE9-gStringData), (Str_0C0B-gStringData)
    .2byte (Str_0C2E-gStringData), (Str_0C4D-gStringData), (Str_0C6C-gStringData), (Str_0C8C-gStringData), (Str_0CAE-gStringData), (Str_0CCC-gStringData), (Str_0CEB-gStringData), (Str_0D10-gStringData)
    .2byte (Str_0D37-gStringData), (Str_0D5F-gStringData), (Str_0D80-gStringData), (Str_0DA2-gStringData), (Str_0DC1-gStringData), (Str_0DE1-gStringData), (Str_0DFE-gStringData), (Str_0E1B-gStringData)
    .2byte (Str_0E3C-gStringData), (Str_0E57-gStringData), (Str_0E78-gStringData), (Str_0E9C-gStringData), (Str_0EBF-gStringData), (Str_0ED9-gStringData), (Str_0EF4-gStringData), (Str_0F14-gStringData)
    .2byte (Str_0F32-gStringData), (Str_0F57-gStringData), (Str_0F74-gStringData), (Str_0F97-gStringData), (Str_0FBD-gStringData), (Str_0FDC-gStringData), (Str_1000-gStringData), (Str_1020-gStringData)
    .2byte (Str_1045-gStringData), (Str_1057-gStringData), (Str_1069-gStringData), (Str_107A-gStringData), (Str_108C-gStringData), (Str_10AB-gStringData), (Str_10D0-gStringData), (Str_10F2-gStringData)
    .2byte (Str_1116-gStringData), (Str_1138-gStringData), (Str_115C-gStringData), (Str_1175-gStringData), (Str_118F-gStringData), (Str_11AD-gStringData), (Str_11CE-gStringData), (Str_11F0-gStringData)
    .2byte (Str_1216-gStringData), (Str_1238-gStringData), (Str_125B-gStringData), (Str_127C-gStringData), (Str_129C-gStringData), (Str_12BE-gStringData), (Str_12DB-gStringData), (Str_12FC-gStringData)
    .2byte (Str_1317-gStringData), (Str_1340-gStringData), (Str_1366-gStringData), (Str_1384-gStringData), (Str_13A6-gStringData), (Str_13C9-gStringData), (Str_13ED-gStringData), (Str_1408-gStringData)
    .2byte (Str_1428-gStringData), (Str_1449-gStringData), (Str_146C-gStringData), (Str_1490-gStringData), (Str_14B0-gStringData), (Str_14D8-gStringData), (Str_1500-gStringData), (Str_152B-gStringData)
    .2byte (Str_1552-gStringData), (Str_157A-gStringData), (Str_15A8-gStringData), (Str_15CF-gStringData), (Str_15F7-gStringData), (Str_1619-gStringData), (Str_163A-gStringData), (Str_1657-gStringData)
    .2byte (Str_1675-gStringData), (Str_169F-gStringData), (Str_16A2-gStringData), (Str_16A2-gStringData), (Str_16A2-gStringData), (Str_16B0-gStringData), (Str_16BD-gStringData), (Str_16D7-gStringData)
    .2byte (Str_16E5-gStringData), (Str_16F3-gStringData), (Str_1701-gStringData), (Str_171B-gStringData), (Str_172B-gStringData), (Str_1739-gStringData), (Str_1742-gStringData), (Str_174A-gStringData)
    .2byte (Str_1752-gStringData), (Str_175C-gStringData), (Str_1768-gStringData), (Str_1779-gStringData), (Str_1799-gStringData), (Str_17AD-gStringData), (Str_17BF-gStringData), (Str_17D0-gStringData)
    .2byte (Str_17EA-gStringData), (Str_17FF-gStringData), (Str_1814-gStringData), (Str_1828-gStringData), (Str_183C-gStringData), (Str_184D-gStringData), (Str_185A-gStringData), (Str_1866-gStringData)
    .2byte (Str_187C-gStringData), (Str_1889-gStringData), (Str_18A0-gStringData), (Str_18B5-gStringData), (Str_18CD-gStringData), (Str_18CD-gStringData), (Str_18CD-gStringData), (Str_18CD-gStringData)
    .2byte (Str_18CD-gStringData), (Str_18CD-gStringData), (Str_18CD-gStringData), (Str_18CD-gStringData), (Str_18CD-gStringData), (Str_18CD-gStringData), (Str_18CD-gStringData), (Str_18CD-gStringData)
    .2byte (Str_18CD-gStringData), (Str_18CD-gStringData), (Str_18CD-gStringData), (Str_18CD-gStringData), (Str_18CD-gStringData), (Str_18CD-gStringData), (Str_18CD-gStringData), (Str_18CD-gStringData)
    .2byte (Str_18CD-gStringData), (Str_18CD-gStringData), (Str_18CD-gStringData), (Str_18CD-gStringData), (Str_18CD-gStringData), (Str_18CD-gStringData), (Str_18CD-gStringData), (Str_18CD-gStringData)
    .2byte (Str_18CD-gStringData), (Str_18D8-gStringData), (Str_18E9-gStringData), (Str_18F3-gStringData), (Str_18FF-gStringData), (Str_1915-gStringData), (Str_192C-gStringData), (Str_1937-gStringData)
    .2byte (Str_193F-gStringData), (Str_1956-gStringData), (Str_1969-gStringData), (Str_197C-gStringData), (Str_198E-gStringData), (Str_19A9-gStringData), (Str_19BF-gStringData), (Str_19CC-gStringData)
    .2byte (Str_19CC-gStringData), (Str_19CC-gStringData), (Str_19CC-gStringData), (Str_19CC-gStringData), (Str_19CC-gStringData), (Str_19CC-gStringData), (Str_19CC-gStringData), (Str_19CC-gStringData)
    .2byte (Str_19CC-gStringData), (Str_19CC-gStringData), (Str_19CC-gStringData), (Str_19CC-gStringData), (Str_19CC-gStringData), (Str_19CC-gStringData), (Str_19CC-gStringData), (Str_19CC-gStringData)
    .2byte (Str_19CC-gStringData), (Str_19CC-gStringData), (Str_19CC-gStringData), (Str_19CC-gStringData), (Str_19E4-gStringData), (Str_19F4-gStringData), (Str_1A00-gStringData), (Str_1A1E-gStringData)
    .2byte (Str_1A2E-gStringData), (Str_1A2E-gStringData), (Str_1A2E-gStringData), (Str_1A2E-gStringData), (Str_1A2E-gStringData), (Str_1A2E-gStringData), (Str_1A2E-gStringData), (Str_1A2E-gStringData)
    .2byte (Str_1A2E-gStringData), (Str_1A2E-gStringData), (Str_1A2E-gStringData), (Str_1A3D-gStringData), (Str_1A4A-gStringData), (Str_1A4A-gStringData), (Str_1A4A-gStringData), (Str_1A4A-gStringData)
    .2byte (Str_1A4A-gStringData), (Str_1A4A-gStringData), (Str_1A4A-gStringData), (Str_1A4A-gStringData), (Str_1A4A-gStringData), (Str_1A4A-gStringData), (Str_1A4A-gStringData), (Str_1A4A-gStringData)
    .2byte (Str_1A4A-gStringData), (Str_1A4A-gStringData), (Str_1A4A-gStringData), (Str_1A4A-gStringData), (Str_1A4A-gStringData), (Str_1A4A-gStringData), (Str_1A4A-gStringData), (Str_1A4A-gStringData)
    .2byte (Str_1A4A-gStringData), (Str_1A4A-gStringData), (Str_1A4A-gStringData), (Str_1A4A-gStringData), (Str_1A4A-gStringData), (Str_1A4A-gStringData), (Str_1A4A-gStringData), (Str_1A4A-gStringData)
    .2byte (Str_1A4A-gStringData), (Str_1A4A-gStringData), (Str_1A4A-gStringData), (Str_1A4A-gStringData), (Str_1A4A-gStringData), (Str_1A4A-gStringData), (Str_1A4A-gStringData), (Str_1A4A-gStringData)
    .2byte (Str_1A4A-gStringData), (Str_1A4A-gStringData), (Str_1A4A-gStringData), (Str_1A54-gStringData), (Str_1A5A-gStringData), (Str_1A63-gStringData), (Str_1A6C-gStringData), (Str_1A73-gStringData)
    .2byte (Str_1A79-gStringData), (Str_1A80-gStringData), (Str_1A87-gStringData), (Str_1A92-gStringData), (Str_1A9B-gStringData), (Str_1AA4-gStringData), (Str_1AAE-gStringData), (Str_1AB6-gStringData)
    .2byte (Str_1AD3-gStringData), (Str_1B0A-gStringData), (Str_1B3E-gStringData), (Str_1B6B-gStringData), (Str_1B94-gStringData), (Str_1BE0-gStringData), (Str_1C12-gStringData), (Str_1C48-gStringData)
    .2byte (Str_1C71-gStringData), (Str_1CAC-gStringData), (Str_1CD2-gStringData), (Str_1D11-gStringData), (Str_1D1A-gStringData), (Str_1D33-gStringData), (Str_1D42-gStringData), (Str_1D46-gStringData)
    .2byte (Str_1D5A-gStringData), (Str_1D5A-gStringData), (Str_1D5A-gStringData), (Str_1D5A-gStringData), (Str_1D5A-gStringData), (Str_1D5A-gStringData), (Str_1D5A-gStringData), (Str_1D5A-gStringData)
    .2byte (Str_1D5A-gStringData), (Str_1D5A-gStringData), (Str_1D5A-gStringData), (Str_1D5A-gStringData), (Str_1D5A-gStringData), (Str_1D5A-gStringData), (Str_1D5A-gStringData), (Str_1D5A-gStringData)
    .2byte (Str_1D5A-gStringData), (Str_1D5A-gStringData), (Str_1D5A-gStringData), (Str_1D5A-gStringData), (Str_1D5A-gStringData), (Str_1D5A-gStringData), (Str_1D5A-gStringData), (Str_1D5A-gStringData)
    .2byte (Str_1D5A-gStringData), (Str_1D5A-gStringData), (Str_1D5A-gStringData), (Str_1D5A-gStringData), (Str_1D5A-gStringData), (Str_1D5A-gStringData), (Str_1D5A-gStringData), (Str_1D62-gStringData)
    .2byte (Str_1D6A-gStringData), (Str_1D72-gStringData), (Str_1D7A-gStringData), (Str_1D82-gStringData), (Str_1D8A-gStringData), (Str_1D99-gStringData), (Str_1DA6-gStringData), (Str_1DC2-gStringData)
    .2byte (Str_1DD6-gStringData), (Str_1DE4-gStringData), (Str_1DF2-gStringData), (Str_1E04-gStringData), (Str_1E16-gStringData), (Str_1E24-gStringData), (Str_1E32-gStringData), (Str_1E3A-gStringData)
    .2byte (Str_1E42-gStringData), (Str_1E4A-gStringData), (Str_1E52-gStringData), (Str_1E5C-gStringData), (Str_1E66-gStringData), (Str_1E70-gStringData), (Str_1E7A-gStringData), (Str_1E84-gStringData)
    .2byte (Str_1E8E-gStringData), (Str_1E98-gStringData), (Str_1EA2-gStringData), (Str_1EAB-gStringData), (Str_1EB4-gStringData), (Str_1EB4-gStringData), (Str_1EB4-gStringData), (Str_1EB4-gStringData)
    .2byte (Str_1EB4-gStringData), (Str_1EB4-gStringData), (Str_1EB4-gStringData), (Str_1EB4-gStringData), (Str_1EB4-gStringData), (Str_1EB4-gStringData), (Str_1EB4-gStringData), (Str_24A0-gStringData)
    .2byte (Str_24A0-gStringData), (Str_24A0-gStringData), (Str_24A0-gStringData), (Str_24A0-gStringData), (Str_24A0-gStringData), (Str_24A0-gStringData), (Str_24A0-gStringData), (Str_24A0-gStringData)
    .2byte (Str_24A0-gStringData), (Str_24A0-gStringData), (Str_24A0-gStringData), (Str_24A0-gStringData), (Str_24A0-gStringData), (Str_24A0-gStringData), (Str_24A0-gStringData), (Str_24A0-gStringData)
    .2byte (Str_24A0-gStringData), (Str_24A0-gStringData), (Str_24A0-gStringData), (Str_24A0-gStringData), (Str_24A0-gStringData), (Str_24A0-gStringData), (Str_24A0-gStringData), (Str_24A0-gStringData)
    .2byte (Str_24A0-gStringData), (Str_24A0-gStringData), (Str_24A0-gStringData), (Str_24A0-gStringData), (Str_24A0-gStringData), (Str_24A0-gStringData), (Str_24A0-gStringData), (Str_24A0-gStringData)
    .2byte (Str_24A0-gStringData), (Str_24A0-gStringData), (Str_24A0-gStringData), (Str_24A0-gStringData), (Str_24A0-gStringData), (Str_24A0-gStringData), (Str_24A0-gStringData), (Str_24A0-gStringData)
    .2byte (Str_24A0-gStringData), (Str_24A0-gStringData), (Str_24A0-gStringData), (Str_24A0-gStringData), (Str_24A0-gStringData), (Str_24A0-gStringData), (Str_24A0-gStringData), (Str_24A0-gStringData)
    .2byte (Str_24A0-gStringData), (Str_24A0-gStringData), (Str_24A0-gStringData), (Str_24A0-gStringData), (Str_24A0-gStringData), (Str_24A0-gStringData), (Str_24A0-gStringData), (Str_24A0-gStringData)
    .2byte (Str_24A0-gStringData), (Str_24A0-gStringData), (Str_24A0-gStringData), (Str_24A0-gStringData), (Str_24A0-gStringData), (Str_24A0-gStringData), (Str_24A0-gStringData), (Str_24A0-gStringData)
    .2byte (Str_24A0-gStringData), (Str_24A0-gStringData), (Str_24A0-gStringData), (Str_24A0-gStringData), (Str_24A0-gStringData), (Str_24A0-gStringData), (Str_24A0-gStringData), (Str_24A0-gStringData)
    .2byte (Str_24A0-gStringData), (Str_24A0-gStringData), (Str_24A0-gStringData), (Str_24A0-gStringData), (Str_24A0-gStringData), (Str_24A0-gStringData), (Str_24A0-gStringData), (Str_24A0-gStringData)
    .2byte (Str_24A0-gStringData), (Str_24A0-gStringData), (Str_24A0-gStringData), (Str_24A0-gStringData), (Str_24A0-gStringData), (Str_24A0-gStringData), (Str_24A0-gStringData), (Str_24A0-gStringData)
    .2byte (Str_24A0-gStringData), (Str_24A0-gStringData), (Str_24A0-gStringData), (Str_24A0-gStringData), (Str_24A0-gStringData), (Str_24A0-gStringData), (Str_24A0-gStringData), (Str_24A0-gStringData)
    .2byte (Str_24A0-gStringData), (Str_24A0-gStringData), (Str_24A0-gStringData), (Str_24A0-gStringData), (Str_24A0-gStringData), (Str_24A0-gStringData), (Str_24A0-gStringData), (Str_24A0-gStringData)
    .2byte (Str_24A0-gStringData), (Str_24A0-gStringData), (Str_24A0-gStringData), (Str_24A0-gStringData), (Str_24A0-gStringData), (Str_24A0-gStringData), (Str_24A0-gStringData), (Str_24A0-gStringData)
    .2byte (Str_24A0-gStringData), (Str_24A0-gStringData), (Str_24A0-gStringData), (Str_24A0-gStringData), (Str_24A0-gStringData), (Str_24A0-gStringData), (Str_24A0-gStringData), (Str_24A0-gStringData)
    .2byte (Str_24A0-gStringData), (Str_24A0-gStringData), (Str_24A0-gStringData), (Str_24A0-gStringData), (Str_24A0-gStringData), (Str_24A0-gStringData), (Str_24A0-gStringData), (Str_24A0-gStringData)
    .2byte (Str_24A0-gStringData), (Str_24A0-gStringData), (Str_24A0-gStringData), (Str_24A0-gStringData), (Str_24A0-gStringData), (Str_24A0-gStringData), (Str_24A0-gStringData), (Str_24A0-gStringData)
    .2byte (Str_24A0-gStringData), (Str_24A0-gStringData), (Str_24A0-gStringData), (Str_24A0-gStringData), (Str_24A0-gStringData), (Str_24A0-gStringData), (Str_24A0-gStringData), (Str_24A0-gStringData)
    .2byte (Str_24A0-gStringData), (Str_24A0-gStringData), (Str_24A0-gStringData), (Str_24A0-gStringData), (Str_24A0-gStringData), (Str_24D4-gStringData), (Str_250B-gStringData), (Str_2533-gStringData)
    .2byte (Str_2558-gStringData), (Str_257D-gStringData), (Str_25B1-gStringData), (Str_25F5-gStringData), (Str_2639-gStringData), (Str_2681-gStringData), (Str_26BC-gStringData), (Str_26F6-gStringData)
    .2byte (Str_2735-gStringData), (Str_2775-gStringData), (Str_27B0-gStringData), (Str_27F6-gStringData), (Str_2838-gStringData), (Str_287E-gStringData), (Str_28CB-gStringData), (Str_2912-gStringData)
    .2byte (Str_2951-gStringData), (Str_295C-gStringData), (Str_295E-gStringData), (Str_2965-gStringData), (Str_296F-gStringData), (Str_2973-gStringData), (Str_297A-gStringData), (Str_29A8-gStringData)
    .2byte (Str_29DE-gStringData), (Str_2A0D-gStringData), (Str_2A3E-gStringData), (Str_2A7B-gStringData), (Str_2A9C-gStringData), (Str_2ABD-gStringData), (Str_2AF1-gStringData), (Str_2B14-gStringData)
    .2byte (Str_2B3E-gStringData), (Str_2B6A-gStringData), (Str_2BA3-gStringData), (Str_2BD8-gStringData), (Str_2C0E-gStringData), (Str_2C46-gStringData), (Str_2C69-gStringData), (Str_2C94-gStringData)
    .2byte (Str_2CC1-gStringData), (Str_2CE2-gStringData), (Str_2D06-gStringData), (Str_2D2E-gStringData), (Str_2D57-gStringData), (Str_2D87-gStringData), (Str_2DAE-gStringData), (Str_2DD5-gStringData)
    .2byte (Str_2DF7-gStringData), (Str_2E23-gStringData), (Str_2E50-gStringData), (Str_2E79-gStringData), (Str_2EAA-gStringData), (Str_2ED6-gStringData), (Str_2EFD-gStringData), (Str_2F22-gStringData)
    .2byte (Str_2F47-gStringData), (Str_2F74-gStringData), (Str_2F93-gStringData), (Str_2FBE-gStringData), (Str_2FDB-gStringData), (Str_3001-gStringData), (Str_3030-gStringData), (Str_3053-gStringData)
    .2byte (Str_3076-gStringData), (Str_3092-gStringData), (Str_30B9-gStringData), (Str_30D2-gStringData), (Str_30F6-gStringData), (Str_311D-gStringData), (Str_314A-gStringData), (Str_3175-gStringData)
    .2byte (Str_319D-gStringData), (Str_31B7-gStringData), (Str_31DF-gStringData), (Str_3204-gStringData), (Str_3229-gStringData), (Str_324D-gStringData), (Str_3270-gStringData), (Str_329D-gStringData)
    .2byte (Str_32C5-gStringData), (Str_32EA-gStringData), (Str_3314-gStringData), (Str_3333-gStringData), (Str_3364-gStringData), (Str_338E-gStringData), (Str_33B2-gStringData), (Str_33D9-gStringData)
    .2byte (Str_3403-gStringData), (Str_3432-gStringData), (Str_3461-gStringData), (Str_3490-gStringData), (Str_34BE-gStringData), (Str_34BE-gStringData), (Str_34BE-gStringData), (Str_34BE-gStringData)
    .2byte (Str_34BE-gStringData), (Str_34C4-gStringData), (Str_34CA-gStringData), (Str_34D0-gStringData), (Str_34D6-gStringData), (Str_34DC-gStringData), (Str_34E2-gStringData), (Str_34E8-gStringData)
    .2byte (Str_34EE-gStringData), (Str_34F4-gStringData), (Str_34FA-gStringData), (Str_3500-gStringData), (Str_3506-gStringData), (Str_350C-gStringData), (Str_3512-gStringData), (Str_3518-gStringData)
    .2byte (Str_351E-gStringData), (Str_3524-gStringData), (Str_352A-gStringData), (Str_3530-gStringData), (Str_3536-gStringData), (Str_353C-gStringData), (Str_3542-gStringData), (Str_3548-gStringData)
    .2byte (Str_354E-gStringData), (Str_3554-gStringData), (Str_355A-gStringData), (Str_3560-gStringData), (Str_3566-gStringData), (Str_356C-gStringData), (Str_3572-gStringData), (Str_3578-gStringData)
    .2byte (Str_357E-gStringData), (Str_3584-gStringData), (Str_358A-gStringData), (Str_3590-gStringData), (Str_3596-gStringData), (Str_359C-gStringData), (Str_35A2-gStringData), (Str_35A8-gStringData)
    .2byte (Str_35AE-gStringData), (Str_35B4-gStringData), (Str_35BA-gStringData), (Str_35C0-gStringData), (Str_35C6-gStringData), (Str_35CC-gStringData), (Str_35D2-gStringData), (Str_35D8-gStringData)
    .2byte (Str_35DE-gStringData), (Str_35E4-gStringData), (Str_35EA-gStringData), (Str_35F0-gStringData), (Str_35F6-gStringData), (Str_35FC-gStringData), (Str_3602-gStringData), (Str_3608-gStringData)
    .2byte (Str_360E-gStringData), (Str_3614-gStringData), (Str_361A-gStringData), (Str_3620-gStringData), (Str_3626-gStringData), (Str_362C-gStringData), (Str_3632-gStringData), (Str_3638-gStringData)
    .2byte (Str_363E-gStringData), (Str_3644-gStringData), (Str_364A-gStringData), (Str_3650-gStringData), (Str_3656-gStringData), (Str_365C-gStringData), (Str_3662-gStringData), (Str_3668-gStringData)
    .2byte (Str_366E-gStringData), (Str_3674-gStringData), (Str_367A-gStringData), (Str_3680-gStringData), (Str_3686-gStringData), (Str_368C-gStringData), (Str_3692-gStringData), (Str_3698-gStringData)
    .2byte (Str_369E-gStringData), (Str_36A4-gStringData), (Str_36AA-gStringData), (Str_36B0-gStringData), (Str_36B6-gStringData), (Str_36BC-gStringData), (Str_36C2-gStringData), (Str_36C8-gStringData)
    .2byte (Str_36CE-gStringData), (Str_36D4-gStringData), (Str_36DA-gStringData), (Str_36E0-gStringData), (Str_36E6-gStringData), (Str_36EC-gStringData), (Str_36F2-gStringData), (Str_36F8-gStringData)
    .2byte (Str_36FE-gStringData), (Str_3704-gStringData), (Str_370A-gStringData), (Str_3710-gStringData), (Str_3716-gStringData), (Str_371C-gStringData), (Str_3722-gStringData), (Str_3728-gStringData)
    .2byte (Str_372E-gStringData), (Str_3734-gStringData), (Str_373A-gStringData), (Str_3740-gStringData), (Str_3746-gStringData), (Str_374C-gStringData), (Str_3752-gStringData), (Str_3758-gStringData)
    .2byte (Str_375E-gStringData), (Str_3764-gStringData), (Str_376A-gStringData), (Str_3770-gStringData), (Str_3776-gStringData), (Str_377C-gStringData), (Str_3782-gStringData), (Str_3788-gStringData)
    .2byte (Str_378E-gStringData), (Str_3794-gStringData), (Str_379A-gStringData), (Str_37A0-gStringData), (Str_37A6-gStringData), (Str_37AC-gStringData), (Str_37B2-gStringData), (Str_37B8-gStringData)
    .2byte (Str_37BE-gStringData), (Str_37C4-gStringData), (Str_37CA-gStringData), (Str_37D0-gStringData), (Str_37D6-gStringData), (Str_37DC-gStringData), (Str_37E2-gStringData), (Str_37E8-gStringData)
    .2byte (Str_37EE-gStringData), (Str_37F4-gStringData), (Str_37FA-gStringData), (Str_3800-gStringData), (Str_3806-gStringData), (Str_380C-gStringData), (Str_3812-gStringData), (Str_3818-gStringData)
    .2byte (Str_381E-gStringData), (Str_3824-gStringData), (Str_382A-gStringData), (Str_3830-gStringData), (Str_3836-gStringData), (Str_383C-gStringData), (Str_3842-gStringData), (Str_3848-gStringData)
    .2byte (Str_384E-gStringData), (Str_3854-gStringData), (Str_385A-gStringData), (Str_3860-gStringData), (Str_3866-gStringData), (Str_386C-gStringData), (Str_3872-gStringData), (Str_3878-gStringData)
    .2byte (Str_387E-gStringData), (Str_3884-gStringData), (Str_388A-gStringData), (Str_3890-gStringData), (Str_3896-gStringData), (Str_389C-gStringData), (Str_38A2-gStringData), (Str_38A8-gStringData)
    .2byte (Str_38AE-gStringData), (Str_38B4-gStringData), (Str_38BA-gStringData), (Str_38C0-gStringData), (Str_38C6-gStringData), (Str_38CC-gStringData), (Str_38D2-gStringData), (Str_38D8-gStringData)
    .2byte (Str_38DE-gStringData), (Str_38E4-gStringData), (Str_38EA-gStringData), (Str_38F0-gStringData), (Str_38F6-gStringData), (Str_38FC-gStringData), (Str_38FC-gStringData), (Str_38FC-gStringData)
    .2byte (Str_38FC-gStringData), (Str_38FC-gStringData), (Str_38FC-gStringData), (Str_38FC-gStringData), (Str_38FC-gStringData), (Str_38FC-gStringData), (Str_38FC-gStringData), (Str_3904-gStringData)
    .2byte (Str_390C-gStringData), (Str_3917-gStringData), (Str_3924-gStringData), (Str_3924-gStringData), (Str_3924-gStringData), (Str_3924-gStringData), (Str_3924-gStringData), (Str_3924-gStringData)
    .2byte (Str_3924-gStringData), (Str_3924-gStringData), (Str_3924-gStringData), (Str_3924-gStringData), (Str_3924-gStringData), (Str_3924-gStringData), (Str_3924-gStringData), (Str_3924-gStringData)
    .2byte (Str_3924-gStringData), (Str_3924-gStringData), (Str_3924-gStringData), (Str_3924-gStringData), (Str_3924-gStringData), (Str_3924-gStringData), (Str_3924-gStringData), (Str_3924-gStringData)
    .2byte (Str_3924-gStringData), (Str_3924-gStringData), (Str_3924-gStringData), (Str_3924-gStringData), (Str_3924-gStringData), (Str_3924-gStringData), (Str_3924-gStringData), (Str_3924-gStringData)
    .2byte (Str_3924-gStringData), (Str_3924-gStringData), (Str_3924-gStringData), (Str_3924-gStringData), (Str_3924-gStringData), (Str_3924-gStringData), (Str_3924-gStringData), (Str_3924-gStringData)
    .2byte (Str_3924-gStringData), (Str_3924-gStringData), (Str_3924-gStringData), (Str_3924-gStringData), (Str_3924-gStringData), (Str_3924-gStringData), (Str_3924-gStringData), (Str_3924-gStringData)
    .2byte (Str_3924-gStringData), (Str_3924-gStringData), (Str_3924-gStringData), (Str_3924-gStringData), (Str_3924-gStringData), (Str_3924-gStringData), (Str_3924-gStringData), (Str_3924-gStringData)
    .2byte (Str_3924-gStringData), (Str_3924-gStringData), (Str_3924-gStringData), (Str_3924-gStringData), (Str_3924-gStringData), (Str_3924-gStringData), (Str_3924-gStringData), (Str_3924-gStringData)
    .2byte (Str_3924-gStringData), (Str_3924-gStringData), (Str_3924-gStringData), (Str_3924-gStringData), (Str_3924-gStringData), (Str_3924-gStringData), (Str_3924-gStringData), (Str_3924-gStringData)
    .2byte (Str_3924-gStringData), (Str_3924-gStringData), (Str_3924-gStringData), (Str_3924-gStringData), (Str_3924-gStringData), (Str_3924-gStringData), (Str_3924-gStringData), (Str_3924-gStringData)
    .2byte (Str_3924-gStringData), (Str_3924-gStringData), (Str_3924-gStringData), (Str_3924-gStringData), (Str_3924-gStringData), (Str_3924-gStringData), (Str_3924-gStringData), (Str_3924-gStringData)
    .2byte (Str_3924-gStringData), (Str_3924-gStringData), (Str_3924-gStringData), (Str_3924-gStringData), (Str_3924-gStringData), (Str_3924-gStringData), (Str_3924-gStringData), (Str_3924-gStringData)
    .2byte (Str_3924-gStringData), (Str_392A-gStringData), (Str_39B3-gStringData), (Str_3A51-gStringData), (Str_3AEE-gStringData), (Str_3B68-gStringData), (Str_3C0A-gStringData), (Str_3C97-gStringData)

gStringData:: @ 0x08372aa0

@ EN: ▷
sCursor:: @ 0x08372aa0
Str_0000:
  .string "▷$"
Str_0002:
.if ENGLISH
  .string "NO DATA$"
.else
  .string "データがありません$"
.endif
Str_000C:
.if ENGLISH
  .string "CANCEL$"
.else
  .string "やめる$"
.endif
Str_0010:
  .string "{RED}H$"
Str_0013:
  .string "{RED}U$"
Str_0016:
  .string "X$"
Str_0018:
  .string "/$"
Str_001A:
  .string ":$"
Str_001C:
.if ENGLISH
  .string "'$"
.else
  .byte 0xD0, 0xFF
.endif
Str_001E:
.if ENGLISH
  .string "{0xE9}$"
.else
  .byte 0xE9, 0xFF
.endif

@ EN: The legendary Reploid Zero / awoke from a long slumber... / / / With Ciel's Resi
sRecap:: @ 0x08372ac0
  .include "src/data/strings/recap.inc"
Str_02B5:
.if ENGLISH
  .string "Two months later.$"
.else
  .string "あれから2ヶ月後$"
.endif

@ EN: 0
sNumber:: @ 0x08372d60
Str_02C0:
  .string "0$"
Str_02C2:
  .string "1$"
Str_02C4:
  .string "2$"
Str_02C6:
  .string "3$"
Str_02C8:
  .string "4$"
Str_02CA:
  .string "5$"
Str_02CC:
  .string "6$"
Str_02CE:
  .string "7$"
Str_02D0:
  .string "8$"
Str_02D2:
  .string "9$"

@ EN: Lv.F
sRanks:: @ 0x08372d74
Str_02D4:
.if ENGLISH
  .string "Lv.F$"
.else
  .string "レベルF$"
.endif
Str_02D9:
.if ENGLISH
  .string "Lv.E$"
.else
  .string "レベルE$"
.endif
Str_02DE:
.if ENGLISH
  .string "Lv.D$"
.else
  .string "レベルD$"
.endif
Str_02E3:
.if ENGLISH
  .string "Lv.C$"
.else
  .string "レベルC$"
.endif
Str_02E8:
.if ENGLISH
  .string "Lv.B$"
.else
  .string "レベルB$"
.endif
Str_02ED:
.if ENGLISH
  .string "Lv.A$"
.else
  .string "レベルA$"
.endif
Str_02F2:
.if ENGLISH
  .string "Lv.S$"
.else
  .string "レベルS$"
.endif

@ EN: DERELICT SPACECRAFT
sStageNames:: @ 0x08372d97
Str_02F7:
.if ENGLISH
  .string "DERELICT SPACECRAFT$"
.else
  .string "こわれたウチュウセン$"
.endif
Str_0302:
.if ENGLISH
  .string "AEGIS VOLCANO BASE$"
.else
  .string "アグニスかざんの基地$"
.endif
Str_030F:
.if ENGLISH
  .string "OCEANIC HWY RUINS$"
.else
  .string "カイジョウのハイウェイあとち$"
.endif
Str_031E:
.if ENGLISH
  .string "W.R. FACTORY$"
.else
  .string "ヘイキ再生工場$"
.endif
Str_0329:
.if ENGLISH
  .string "OLD RESIDENTIAL$"
.else
  .string "旧きょじゅうく$"
.endif
Str_0332:
.if ENGLISH
  .string "MISSILE FACTORY$"
.else
  .string "ミサイル工場$"
.endif
Str_033A:
.if ENGLISH
  .string "TWILIGHT DESERT$"
.else
  .string "ゆうやみの砂ばく$"
.endif
Str_0344:
.if ENGLISH
  .string "FOREST OF ANATRE$"
.else
  .string "アナトレーのモリ$"
.endif
Str_034D:
.if ENGLISH
  .string "FRONTLINE ICE BASE$"
.else
  .string "コオリのゼンセン基地$"
.endif
Str_035A:
.if ENGLISH
  .string "AREA X-2$"
.else
  .string "エリアX-2$"
.endif
Str_0361:
.if ENGLISH
  .string "ENERGY FACILITY$"
.else
  .string "エネルギーしせつ$"
.endif
Str_036A:
.if ENGLISH
  .string "SNOWY PLAINS$"
.else
  .string "セツゲン$"
.endif
Str_036F:
.if ENGLISH
  .string "SUNKEN LIBRARY$"
.else
  .string "すいぼつしたトショカン$"
.endif
Str_037B:
.if ENGLISH
  .string "GIANT ELEVATOR$"
.else
  .string "巨大エレベーター$"
.endif
Str_0386:
.if ENGLISH
  .string "SUB ARCADIA$"
.else
  .string "アンダー・アルカディア$"
.endif

@ EN: AREA: AEGIS VOLCANO BASE / BOSS: BLAZIN' FLIZARD / MISSION: N.A. ARMY RECON
Text_MissionDesc_00:: @ 0x08372E32
Str_0392:
.if ENGLISH
	.string "AREA: AEGIS VOLCANO BASE\n"
	.string "BOSS: BLAZIN' FLIZARD\n"
	.string "MISSION: N.A. ARMY RECON$"
.else
	.string "エリア  :アグニスかざんの基地\n"
	.string "ボス   :ブレイジン・フリザード\n"
	.string "ミッション:ネオ・アルカディア軍テイサツ$"
.endif

@ EN: AREA: OCEANIC HWY RUINS / BOSS: CHILDRE INARABITTA / MISSION: TRACK D.E. SIGNAL
Text_MissionDesc_01:: @ 0x08372E6D
Str_03CD:
.if ENGLISH
	.string "AREA: OCEANIC HWY RUINS\n"
	.string "BOSS: CHILDRE INARABITTA\n"
	.string "MISSION: TRACK D.E. SIGNAL$"
.else
	.string "エリア  :カイジョウのハイウェイあとち\n"
	.string "ボス   :チルドレ・イナラビッタ\n"
	.string "ミッション:ダークエルフハンノウのカクニン$"
.endif

@ EN: AREA: W.R. FACTORY / BOSS: DEVILBAT SCHILT / MISSION: DESTROY FACTORY
Text_MissionDesc_02:: @ 0x08372EAA
Str_040A:
.if ENGLISH
	.string "AREA: W.R. FACTORY\n"
	.string "BOSS: DEVILBAT SCHILT\n"
	.string "MISSION: DESTROY FACTORY$"
.else
	.string "エリア  :ヘイキ再生工場\n"
	.string "ボス   :ヘルバット・シルト\n"
	.string "ミッション:工場のハカイ$"
.endif

@ EN: AREA: OLD RESIDENTIAL / BOSS: DEATHTANZ MANTISK / MISSION: FIND DARK ELF
Text_MissionDesc_03:: @ 0x08372ED9
Str_0439:
.if ENGLISH
	.string "AREA: OLD RESIDENTIAL\n"
	.string "BOSS: DEATHTANZ MANTISK\n"
	.string "MISSION: FIND DARK ELF$"
.else
	.string "エリア  :旧きょじゅうく\n"
	.string "ボス   :デスタンツ・マンティスク\n"
	.string "ミッション:ダークエルフのチョウサ$"
.endif

@ EN: AREA: TWILIGHT DESERT / BOSS: ANUBIS NECROMANCESS V / MISSION: ENGAGE N.A. ARMY
Text_MissionDesc_04:: @ 0x08372F0D
Str_046D:
.if ENGLISH
	.string "AREA: TWILIGHT DESERT\n"
	.string "BOSS: ANUBIS NECROMANCESS V\n"
	.string "MISSION: ENGAGE N.A. ARMY$"
.else
	.string "エリア  :ゆうやみの砂ばく\n"
	.string "ボス   :アヌビステップ・ネクロマンセス5世\n"
	.string "ミッション:ネオ・アルカディア軍のゲイゲキ$"
.endif

@ EN: AREA: FOREST OF ANATRE / BOSS: HANUMACHINE R / MISSION: ENGAGE N.A. ARMY
Text_MissionDesc_05:: @ 0x08372F4D
Str_04AD:
.if ENGLISH
	.string "AREA: FOREST OF ANATRE\n"
	.string "BOSS: HANUMACHINE R\n"
	.string "MISSION: ENGAGE N.A. ARMY$"
.else
	.string "エリア  :アナトレーのモリ\n"
	.string "ボス   :ハヌマシーンR\n"
	.string "ミッション:ネオ・アルカディア軍のゲイゲキ$"
.endif

@ EN: AREA: FRONTLINE ICE BASE / BOSS: BLIZZACK STAGGROFF R / MISSION: ENGAGE N.A. ARM
Text_MissionDesc_06:: @ 0x08372F81
Str_04E1:
.if ENGLISH
	.string "AREA: FRONTLINE ICE BASE\n"
	.string "BOSS: BLIZZACK STAGGROFF R\n"
	.string "MISSION: ENGAGE N.A. ARMY$"
.else
	.string "エリア  :コオリのゼンセン基地\n"
	.string "ボス   :ブリザック・スタグロフR\n"
	.string "ミッション:ネオ・アルカディア軍のゲイゲキ$"
.endif

@ EN: AREA: AREA X-2 / BOSS: COPY X MARK II / MISSION: INFILTRATE N.A.
Text_MissionDesc_07:: @ 0x08372FBE
Str_051E:
.if ENGLISH
	.string "AREA: AREA X-2\n"
	.string "BOSS: COPY X MARK II\n"
	.string "MISSION: INFILTRATE N.A.$"
.else
	.string "エリア  :エリアX-2\n"
	.string "ボス   :コピーエックスMK2\n"
	.string "ミッション:ネオ・アルカディアせんにゅう$"
.endif

@ EN: AREA: ENERGY FACILITY / BOSS: CUBIT FOXTAR / MISSION: SEARCH FACILITY
Text_MissionDesc_08:: @ 0x08372FF1
Str_0551:
.if ENGLISH
	.string "AREA: ENERGY FACILITY\n"
	.string "BOSS: CUBIT FOXTAR\n"
	.string "MISSION: SEARCH FACILITY$"
.else
	.string "エリア  :エネルギーしせつ\n"
	.string "ボス   :キュービット・フォクスター\n"
	.string "ミッション:しせつのチョウサ$"
.endif

@ EN: AREA: SNOWY PLAINS / BOSS: GLACIER LE CACTANK / MISSION: RETRIEVE DATA
Text_MissionDesc_09:: @ 0x08373023
Str_0583:
.if ENGLISH
	.string "AREA: SNOWY PLAINS\n"
	.string "BOSS: GLACIER LE CACTANK\n"
	.string "MISSION: RETRIEVE DATA$"
.else
	.string "エリア  :セツゲン\n"
	.string "ボス   :グラチャー・レ・カクタンク\n"
	.string "ミッション:データのカイシュウ$"
.endif

@ EN: AREA: SUNKEN LIBRARY / BOSS: VOLTEEL BIBLIO / MISSION: RETRIEVE DATA FILE
Text_MissionDesc_10:: @ 0x08373052
Str_05B2:
.if ENGLISH
	.string "AREA: SUNKEN LIBRARY\n"
	.string "BOSS: VOLTEEL BIBLIO\n"
	.string "MISSION: RETRIEVE DATA FILE$"
.else
	.string "エリア  :すいぼつしたトショカン\n"
	.string "ボス   :ヴォルティール・ビブリーオ\n"
	.string "ミッション:データファイルのカイシュウ$"
.endif

@ EN: AREA: GIANT ELEVATOR / BOSS: TRETISTA KELVERIAN / MISSION: SEARCH FACILITY
Text_MissionDesc_11:: @ 0x0837308C
Str_05EC:
.if ENGLISH
	.string "AREA: GIANT ELEVATOR\n"
	.string "BOSS: TRETISTA KELVERIAN\n"
	.string "MISSION: SEARCH FACILITY$"
.else
	.string "エリア  :巨大エレベーター\n"
	.string "ボス   :トレテスタ・ケルベリアン\n"
	.string "ミッション:しせつのチョウサ$"
.endif

Str_061F:
.if ENGLISH
  .string "Mission already completed.$"
.else
  .string "このミッションは、すでにしゅうりょうしています$"
.endif

@ EN: Martina
sCyberElfNames:: @ 0x083730d7
Str_0637:
.if ENGLISH
  .string "Martina$"
.else
  .string "マルティナ$"
.endif
Str_063D:
.if ENGLISH
  .string "Milvy$"
.else
  .string "ミルピィ$"
.endif
Str_0642:
.if ENGLISH
  .string "Elphy$"
.else
  .string "エルピィ$"
.endif
Str_0647:
.if ENGLISH
  .string "Sylphy$"
.else
  .string "シルピィ$"
.endif
Str_064C:
.if ENGLISH
  .string "Rilphy$"
.else
  .string "レルピィ$"
.endif
Str_0651:
.if ENGLISH
  .string "Artan$"
.else
  .string "アータン$"
.endif
Str_0656:
.if ENGLISH
  .string "Zictan$"
.else
  .string "ジクタン$"
.endif
Str_065B:
.if ENGLISH
  .string "Mott$"
.else
  .string "モット$"
.endif
Str_065F:
.if ENGLISH
  .string "Dott$"
.else
  .string "ドット$"
.endif
Str_0663:
.if ENGLISH
  .string "Curiph$"
.else
  .string "キュリフ$"
.endif
Str_0668:
.if ENGLISH
  .string "Luriph$"
.else
  .string "ルルフ$"
.endif
Str_066C:
.if ENGLISH
  .string "Suriph$"
.else
  .string "スルフ$"
.endif
Str_0670:
.if ENGLISH
  .string "Tiriph$"
.else
  .string "ティリフ$"
.endif
Str_0675:
.if ENGLISH
  .string "Yuriph$"
.else
  .string "ユリフ$"
.endif
Str_0679:
.if ENGLISH
  .string "Beriph$"
.else
  .string "ベリフ$"
.endif
Str_067D:
.if ENGLISH
  .string "Wiliph$"
.else
  .string "ウィリフ$"
.endif
Str_0682:
.if ENGLISH
  .string "Cyliph$"
.else
  .string "クリフ$"
.endif
Str_0686:
.if ENGLISH
  .string "Snoq$"
.else
  .string "スノック$"
.endif
Str_068B:
.if ENGLISH
  .string "Mathiq$"
.else
  .string "マティック$"
.endif
Str_0691:
.if ENGLISH
  .string "Miyaq$"
.else
  .string "ミヤック$"
.endif
Str_0696:
.if ENGLISH
  .string "Ajiq$"
.else
  .string "アジック$"
.endif
Str_069B:
.if ENGLISH
  .string "Dobuq$"
.else
  .string "トブック$"
.endif
Str_06A0:
.if ENGLISH
  .string "Mulaq$"
.else
  .string "ムラック$"
.endif
Str_06A5:
.if ENGLISH
  .string "Mailla$"
.else
  .string "マイーラ$"
.endif
Str_06AA:
.if ENGLISH
  .string "Miulla$"
.else
  .string "ミウーラ$"
.endif
Str_06AF:
.if ENGLISH
  .string "Cloppe$"
.else
  .string "コロップ$"
.endif
Str_06B4:
.if ENGLISH
  .string "Sloppe$"
.else
  .string "ソロップ$"
.endif
Str_06B9:
.if ENGLISH
  .string "Putite$"
.else
  .string "プチット$"
.endif
Str_06BE:
.if ENGLISH
  .string "Balette$"
.else
  .string "バレット$"
.endif
Str_06C3:
.if ENGLISH
  .string "Maya$"
.else
  .string "マーヤ$"
.endif
Str_06C7:
.if ENGLISH
  .string "Kwappa$"
.else
  .string "クワッパ$"
.endif
Str_06CC:
.if ENGLISH
  .string "Gambul$"
.else
  .string "ガンブル$"
.endif
Str_06D1:
.if ENGLISH
  .string "Biraid$"
.else
  .string "バーエイド$"
.endif
Str_06D7:
.if ENGLISH
  .string "Birleaf$"
.else
  .string "バーリーフ$"
.endif
Str_06DD:
.if ENGLISH
  .string "Pitapah$"
.else
  .string "ピタッパ$"
.endif
Str_06E2:
.if ENGLISH
  .string "Pitapuh$"
.else
  .string "ピタップ$"
.endif
Str_06E7:
.if ENGLISH
  .string "Beetack$"
.else
  .string "ビータック$"
.endif
Str_06ED:
.if ENGLISH
  .string "Beenipe$"
.else
  .string "ビーナイプ$"
.endif
Str_06F3:
.if ENGLISH
  .string "Archim$"
.else
  .string "アーチム$"
.endif
Str_06F8:
.if ENGLISH
  .string "Archil$"
.else
  .string "アーチル$"
.endif
Str_06FD:
.if ENGLISH
  .string "Byse$"
.else
  .string "バイッス$"
.endif
Str_0702:
.if ENGLISH
  .string "Dylphina$"
.else
  .string "デルピーナ$"
.endif
Str_0708:
.if ENGLISH
  .string "Lizetus$"
.else
  .string "リゼタス$"
.endif
Str_070D:
.if ENGLISH
  .string "Cottus$"
.else
  .string "コータス$"
.endif
Str_0712:
.if ENGLISH
  .string "Shuthas$"
.else
  .string "シュータス$"
.endif
Str_0718:
.if ENGLISH
  .string "Malthas$"
.else
  .string "マルタス$"
.endif
Str_071D:
.if ENGLISH
  .string "Ilethas$"
.else
  .string "イレタス$"
.endif
Str_0722:
.if ENGLISH
  .string "Enethas$"
.else
  .string "エネタス$"
.endif
Str_0727:
.if ENGLISH
  .string "Busras$"
.else
  .string "バースラス$"
.endif
Str_072D:
.if ENGLISH
  .string "Sabras$"
.else
  .string "セーバラス$"
.endif
Str_0733:
.if ENGLISH
  .string "Roderas$"
.else
  .string "ロードラス$"
.endif
Str_0739:
.if ENGLISH
  .string "Boomeras$"
.else
  .string "ブーメラス$"
.endif
Str_073F:
.if ENGLISH
  .string "Clokkle$"
.else
  .string "クロクル$"
.endif
Str_0744:
.if ENGLISH
  .string "Metoras$"
.else
  .string "メットラス$"
.endif
Str_074A:
.if ENGLISH
  .string "Metorika$"
.else
  .string "メットリカ$"
.endif
Str_0750:
.if ENGLISH
  .string "Metorph$"
.else
  .string "メットルフ$"
.endif
Str_0756:
.if ENGLISH
  .string "Metella$"
.else
  .string "メットレラ$"
.endif
Str_075C:
.if ENGLISH
  .string "Meterom$"
.else
  .string "メットロム$"
.endif
Str_0762:
.if ENGLISH
  .string "Kynite$"
.else
  .string "キーナイト$"
.endif
Str_0768:
.if ENGLISH
  .string "Surnite$"
.else
  .string "サーナイト$"
.endif
Str_076E:
.if ENGLISH
  .string "Tenite$"
.else
  .string "テーナイト$"
.endif
Str_0774:
.if ENGLISH
  .string "Stopalla$"
.else
  .string "ストパーラ$"
.endif
Str_077A:
.if ENGLISH
  .string "Stopina$"
.else
  .string "ストピーナ$"
.endif
Str_0780:
.if ENGLISH
  .string "Stopule$"
.else
  .string "ストプール$"
.endif
Str_0786:
.if ENGLISH
  .string "Stopeta$"
.else
  .string "ストペータ$"
.endif
Str_078C:
.if ENGLISH
  .string "Stoposa$"
.else
  .string "ストポーサ$"
.endif
Str_0792:
.if ENGLISH
  .string "Hanmarga$"
.else
  .string "ハンマーガ$"
.endif
Str_0798:
.if ENGLISH
  .string "Hanmarji$"
.else
  .string "ハンマージ$"
.endif
Str_079E:
.if ENGLISH
  .string "Hanmarbo$"
.else
  .string "ハンマーボ$"
.endif
Str_07A4:
.if ENGLISH
  .string "Aina$"
.else
  .string "エイーナ$"
.endif
Str_07A9:
.if ENGLISH
  .string "Acooi$"
.else
  .string "エコーイ$"
.endif
Str_07AE:
.if ENGLISH
  .string "Achoon$"
.else
  .string "エチューン$"
.endif
Str_07B4:
.if ENGLISH
  .string "Anater$"
.else
  .string "エナータ$"
.endif
Str_07B9:
.if ENGLISH
  .string "Awarne$"
.else
  .string "エワーネ$"
.endif

@ EN: None
sCyberElfMenu:: @ 0x0837325e
Str_07BE:
.if ENGLISH
  .string "None$"
.else
  .string "なし$"
.endif
Str_07C1:
.if ENGLISH
  .string "{RED}Equip SAT.1{RED_END}$"
.else
  .string "{RED}サテライト1そうびちゅう{RED_END}$"
.endif
Str_07D0:
.if ENGLISH
  .string "{RED}Equip SAT.2{RED_END}$"
.else
  .string "{RED}サテライト2そうびちゅう{RED_END}$"
.endif
Str_07DF:
.if ENGLISH
  .string "Fusion elves\n"
  .string "will die\n"
  .string "when used.$"
.else
  .string "フュージョン系エルフは\n1回 使用すると\n死んでしまいます$"
.endif
Str_0802:
.if ENGLISH
  .string "Raise and\n"
  .string "upgrade your\n"
  .string "Cyber-elves.$"
.else
  .string "サイバーエルフを\nそだてたり\n改造したりします$"
.endif
Str_081C:
.if ENGLISH
  .string "You can see\n"
  .string "a list of\n"
  .string "Cyber-elves.$"
.else
  .string "げんざい もっている\nサイバーエルフの\nリストが見られます$"
.endif

@ EN: Select and press A BUTTON.
sCyberElfMenu2:: @ 0x083732db
Str_083B:
.if ENGLISH
  .string "Select and press A BUTTON.$"
.else
  .string "上下でえらんで Aボタンをおしてください$"
.endif
Str_0852:
.if ENGLISH
  .string "Elves that\n"
  .string "boost\n"
  .string "vitality.$"
.else
  .string "ライフにかんする\nサポートをする\nエルフたちです$"
.endif
Str_086B:
.if ENGLISH
  .string "Elves that\n"
  .string "boost\n"
  .string "movement or\n"
  .string "help attack.$"
.else
  .string "プレイヤーのイドウ系\nアビリティーを高めたり\nコウゲキのほじょをする\nエルフたちです$"
.endif
Str_0898:
.if ENGLISH
  .string "Elves that\n"
  .string "assist with\n"
  .string "mission data\n"
  .string "and weapons.$"
.else
  .string "エリアやミッションの\nデータやプレイヤーの\nブキ系アビリティーを\n高めるエルフたちです$"
.endif
Str_08C6:
.if ENGLISH
  .string "Left or Right chooses a tag.$"
.else
  .string "左右でタグをえらんでください$"
.endif
Str_08D7:
.if ENGLISH
  .string "Select and press A BUTTON.$"
.else
  .string "✚ボタンでえらんで Aボタンをおしてください$"
.endif
Str_08EF:
.if ENGLISH
  .string "Select and press A BUTTON.$"
.else
  .string "✚ボタンでえらんで Aボタンをおしてください$"
.endif
Str_0907:
.if ENGLISH
  .string "EC:Need/Hold$"
.else
  .string "ひつよう/もっているEC$"
.endif

@ EN: Upgrade one / level? / Yes No
Text_CyberElfGrowUp00:: @ 0x083733B4
Str_0914:
.if ENGLISH
	.string "Upgrade one\n"
	.string "level?\n"
	.string "  Yes   No$"
.else
	.string "1だんかい\n"
	.string "せいちょうさせますか？\n"
	.string "  はい   いいえ$"
.endif

@ EN: Upgrade to / Satellite? / Yes No
Text_CyberElfGrowUp01:: @ 0x083733D1
Str_0931:
.if ENGLISH
	.string "Upgrade to\n"
	.string "Satellite?\n"
	.string "  Yes   No$"
.else
	.string "サテライトタイプに\n"
	.string "改造しますか？\n"
	.string "  はい   いいえ$"
.endif

@ EN: Upgrade to / Fusion type? / Yes No
Text_CyberElfGrowUp02:: @ 0x083733F0
Str_0950:
.if ENGLISH
	.string "Upgrade to\n"
	.string "Fusion type?\n"
	.string "  Yes   No$"
.else
	.string "フュージョンタイプに\n"
	.string "改造しますか？\n"
	.string "  はい   いいえ$"
.endif

@ EN: Upgrade to / new version? / Yes No
Text_CyberElfGrowUp03:: @ 0x08373410
Str_0970:
.if ENGLISH
	.string "Upgrade to\n"
	.string "new version?\n"
	.string "  Yes   No$"
.else
	.string "ヴァージョンアップ\n"
	.string "改造しますか？\n"
	.string "  はい   いいえ$"
.endif

@ EN: Select and press A BUTTON.
str_0837342f:: @ 0x0837342f
Str_098F:
.if ENGLISH
  .string "Select and press A BUTTON.$"
.else
  .string "✚ボタンでえらんで Aボタンをおしてください$"
.endif
Str_09A7:
.if ENGLISH
  .string "Select and press A BUTTON.$"
.else
  .string "✚ボタンでえらんで Aボタンをおしてください$"
.endif

@ EN: EC
sEC:: @ 0x0837345f
Str_09BF:
  .string "EC$"

@ EN: Satellite 1 / not equipped / with an Elf.
sNoSatelite:: @ 0x08373462
Str_09C2:
.if ENGLISH
  .string "Satellite 1\n"
  .string "not equipped\n"
  .string "with an Elf.$"
.else
  .string "げんざいサテライト1に\nエルフはそうびされて\nいません$"
.endif
Str_09DE:
.if ENGLISH
  .string "Satellite 2\n"
  .string "not equipped\n"
  .string "with an Elf.$"
.else
  .string "げんざいサテライト2に\nエルフはそうびされて\nいません$"
.endif

@ EN: Insufficient E-Crystals.
s_0837349a:: @ 0x0837349a
Str_09FA:
.if ENGLISH
  .string "Insufficient E-Crystals.$"
.else
  .string "Eクリスタルがたりません$"
.endif
Str_0A07:
.if ENGLISH
  .string "Can't upgrade when equipped.$"
.else
  .string "そうびちゅうは 改造できません$"
.endif
Str_0A19:
.if ENGLISH
  .string "Elf converted to Sub Tank!$"
.else
  .string "エルフがサブタンクにかわった！$"
.endif

@ EN: I double / your / vitality.
Text_Cyberelfs:: @ 0x083734c9
  .include "src/data/strings/cyberelf.inc"

@ EN: None
sNothing:: @ 0x0837413f
Str_169F:
.if ENGLISH
  .string "None$"
.else
  .string "なし$"
.endif

@ EN: Your main weapon.
s_08374142:: @ 0x08374142
Str_16A2:
.if ENGLISH
  .string "Your main weapon.$"
.else
  .string "メインでそうびしているブキ$"
.endif
Str_16B0:
.if ENGLISH
  .string "Your sub weapon.$"
.else
  .string "サブでそうびしているブキ$"
.endif
Str_16BD:
.if ENGLISH
  .string "Tank for extra Life Energy.$"
.else
  .string "よぶんにとったライフエネルギーをためておけるタンク$"
.endif
Str_16D7:
.if ENGLISH
  .string "Your Head Chip.$"
.else
  .string "そうびしているヘッドチップ$"
.endif
Str_16E5:
.if ENGLISH
  .string "Your Body Chip.$"
.else
  .string "そうびしているボディチップ$"
.endif
Str_16F3:
.if ENGLISH
  .string "Your Foot Chip.$"
.else
  .string "そうびしているフットチップ$"
.endif

@ EN: Abort completed missions.
@ AP: Press A to return to hub.
sEscape:: @ 0x083741a1
Str_1701:
.if AP
  .string "Press A to return to hub.$"
.elseif ENGLISH
  .string "Abort completed missions.$"
.else
  .string "ボスをたおしたエリアなら、いつでもだっしゅつできる$"
.endif
Str_171B:
.if ENGLISH
  .string "A BUTTON:Esc B BUTTON:Cancel$"
.else
  .string "A:エスケープ B:キャンセル$"
.endif
Str_172B:
.if ENGLISH
  .string "You can't escape now!$"
.else
  .string "今はエスケープできません$"
.endif

@ EN: BUSTER SHOT
sWeaponNames:: @ 0x083741d9
Str_1739:
.if ENGLISH
  .string "BUSTER SHOT$"
.else
  .string "バスターショット$"
.endif
Str_1742:
.if ENGLISH
  .string "Z SABER$"
.else
  .string "ゼットセイバー$"
.endif
Str_174A:
.if ENGLISH
  .string "RECOIL ROD$"
.else
  .string "リコイルロッド$"
.endif
Str_1752:
.if ENGLISH
  .string "S.BOOMERANG$"
.else
  .string "シールドブーメラン$"
.endif

@ EN: Remaining energy:
sSubtankRemaining:: @ 0x083741fc
Str_175C:
.if ENGLISH
  .string "Remaining energy:$"
.else
  .string "エネルギーざんりょう:$"
.endif

@ EN: A normal Head Chip.
sChipEffects:: @ 0x08374208
Str_1768:
.if ENGLISH
  .string "A normal Head Chip.$"
.else
  .string "ノーマルじょうたいのヘッドチップ$"
.endif
Str_1779:
.if ENGLISH
  .string "Heals when standing still.$"
.else
  .string "たち止まっていると自動的に体力をかいふくしてくれる$"
.endif
Str_1799:
.if ENGLISH
  .string "Auto-charges weapon.$"
.else
  .string "自動的にブキをチャージしてくれる$"
.endif
Str_17AD:
.if ENGLISH
  .string "Boosts weapon charge speed.$"
.else
  .string "ブキのチャージ時間がはやくなる$"
.endif
Str_17BF:
.if ENGLISH
  .string "A normal Body Chip.$"
.else
  .string "ノーマルじょうたいのボディチップ$"
.endif
Str_17D0:
.if ENGLISH
  .string "Ignores crumbling terrain.$"
.else
  .string "しずんだり くずれたりする地形を ムコウにする$"
.endif
Str_17EA:
.if ENGLISH
  .string "No recoil when hit.$"
.else
  .string "コウゲキをうけても あとずさりしなくなる$"
.endif
Str_17FF:
.if ENGLISH
  .string "Enables Thunder attack.$"
.else
  .string "カミナリぞくせいのコウゲキがカノウになる$"
.endif
Str_1814:
.if ENGLISH
  .string "Enables Flame attack.$"
.else
  .string "ホノオぞくせいのコウゲキがカノウになる$"
.endif
Str_1828:
.if ENGLISH
  .string "Enables Ice attack.$"
.else
  .string "コオリぞくせいのコウゲキがカノウになる$"
.endif
Str_183C:
.if ENGLISH
  .string "A normal Foot Chip.$"
.else
  .string "ノーマルじょうたいのフットチップ$"
.endif
Str_184D:
.if ENGLISH
  .string "Can jump on water.$"
.else
  .string "すいめんをジャンプできる$"
.endif
Str_185A:
.if ENGLISH
  .string "Can double jump.$"
.else
  .string "2だんジャンプができる$"
.endif
Str_1866:
.if ENGLISH
  .string "Can dash through some foes.$"
.else
  .string "とくていのテキをダッシュで すりぬけられる$"
.endif
Str_187C:
.if ENGLISH
  .string "Boosts running speed.$"
.else
  .string "はしるはやさがアップする$"
.endif
Str_1889:
.if ENGLISH
  .string "Ignores slippery terrain.$"
.else
  .string "すべる地めんの上でも ふつうに はしれる$"
.endif
Str_18A0:
.if ENGLISH
  .string "Slower sliding down walls.$"
.else
  .string "かべから ずりおちるそくどが おそくなる$"
.endif
Str_18B5:
.if ENGLISH
  .string "All Foot Chip traits on.$"
.else
  .string "すべてのフットチップの力が使えるようになる$"
.endif

sElfVoices: @ 0x0837436d
Str_18CD:
.if ENGLISH
  .string "{RED}Job Complete{RED_END}$"
.else
  .string "わ〜、いただきます！$"
.endif
.if ENGLISH
Str_18D8 = Str_18CD  @ US shares one copy
.else
Str_18D8:
  .string "わ〜い、わ〜い\nEクリスタルだ！$"
.endif
.if ENGLISH
Str_18E9 = Str_18CD  @ US shares one copy
.else
Str_18E9:
  .string "ありがとう〜ゼロ！$"
.endif
.if ENGLISH
Str_18F3 = Str_18CD  @ US shares one copy
.else
Str_18F3:
  .string "おんにきるよ！\nゼロ！$"
.endif
.if ENGLISH
Str_18FF = Str_18CD  @ US shares one copy
.else
Str_18FF:
  .string "ゼロ、ここまで\nそだててくれて\nありがとう$"
.endif
.if ENGLISH
Str_1915 = Str_18CD  @ US shares one copy
.else
Str_1915:
  .string "なにもかも\nゼロのおかげだよ！\nありがとう！$"
.endif
.if ENGLISH
Str_192C = Str_18CD  @ US shares one copy
.else
Str_192C:
  .string "ごちそうさまでした！$"
.endif
.if ENGLISH
Str_1937 = Str_18CD  @ US shares one copy
.else
Str_1937:
  .string "いただきます！$"
.endif
.if ENGLISH
Str_193F = Str_18CD  @ US shares one copy
.else
Str_193F:
  .string "こんなんじゃ\nたりないよ\nもっとちょうだ〜い$"
.endif
.if ENGLISH
Str_1956 = Str_18CD  @ US shares one copy
.else
Str_1956:
  .string "おなかすいたよう\nもっとほしいよう！$"
.endif
.if ENGLISH
Str_1969 = Str_18CD  @ US shares one copy
.else
Str_1969:
  .string "もうすこしたべれば\n大きくなれるわ$"
.endif
.if ENGLISH
Str_197C = Str_18CD  @ US shares one copy
.else
Str_197C:
  .string "もうちょっとで\nパワーアップするぜ$"
.endif
.if ENGLISH
Str_198E = Str_18CD  @ US shares one copy
.else
Str_198E:
  .string "Eクリスタル\nう〜んとたべて\nゼロの力になりたいな$"
.endif
.if ENGLISH
Str_19A9 = Str_18CD  @ US shares one copy
.else
Str_19A9:
  .string "Eクリスタルの力で\nパワーアップしたいな$"
.endif
.if ENGLISH
Str_19BF = Str_18CD  @ US shares one copy
.else
Str_19BF:
  .string "{RED}シメイを終えました{RED_END}$"
.endif

@ EN: OK to save the current data? / YES / NO
sSave:: @ 0x0837446c
Str_19CC:
.if ENGLISH
  .string "OK to save the current data?\n"
  .string "  YES\n"
  .string "  NO$"
.else
  .string "データをセーブしますか？\n  はい\n  いいえ$"
.endif
Str_19E4:
.if ENGLISH
  .string "To which file?$"
.else
  .string "どこにデータをセーブしますか？$"
.endif
Str_19F4:
.if ENGLISH
  .string "Data has been saved.$"
.else
  .string "データをセーブしました$"
.endif
Str_1A00:
.if ENGLISH
  .string "Okay to overwrite?\n"
  .string "  YES\n"
  .string "  NO$"
.else
  .string "このデータに上がきしていいですか？\n  はい\n  いいえ$"
.endif
Str_1A1E:
.if ENGLISH
  .string "Data has been overwriten.$"
.else
  .string "データを上がきセーブしました$"
.endif

@ EN: ReflectLaser
sUnused_083744ce:: @ 0x083744ce
Str_1A2E:
.if ENGLISH
  .string "ReflectLaser$"
.else
  .string "「NEWレジスタンスベース」$"
.endif
.if ENGLISH
Str_1A3D = Str_1A2E  @ US shares one copy
.else
Str_1A3D:
  .string "「メンテナンス・ルーム」$"
.endif

@ EN: ReflectLaser
sExSkillNames:: @ 0x083744ea
.if ENGLISH
Str_1A4A = Str_1A2E  @ US shares one copy
.else
Str_1A4A:
  .string "リフレクトレーザー$"
.endif
Str_1A54:
.if ENGLISH
  .string "V-Shot$"
.else
  .string "Vショット$"
.endif
Str_1A5A:
.if ENGLISH
  .string "BurstShot$"
.else
  .string "バーストショット$"
.endif
Str_1A63:
.if ENGLISH
  .string "BlizzrdArrow$"
.else
  .string "ブリザードアロー$"
.endif
Str_1A6C:
.if ENGLISH
  .string "GaleAttack$"
.else
  .string "レップウゲキ$"
.endif
Str_1A73:
.if ENGLISH
  .string "SaberSmash$"
.else
  .string "ラクサイガ$"
.endif
Str_1A79:
.if ENGLISH
  .string "SplitHeavens$"
.else
  .string "テンレツジン$"
.endif
Str_1A80:
.if ENGLISH
  .string "ThrowBlade$"
.else
  .string "ザンエイダン$"
.endif
Str_1A87:
.if ENGLISH
  .string "1000 Slash$"
.else
  .string "サウザンドスラッシュ$"
.endif
Str_1A92:
.if ENGLISH
  .string "SoulLauncher$"
.else
  .string "ソウルランチャー$"
.endif
Str_1A9B:
.if ENGLISH
  .string "ShieldSweep$"
.else
  .string "クロールシールド$"
.endif
Str_1AA4:
.if ENGLISH
  .string "OrbitShield$"
.else
  .string "サーキュラシールド$"
.endif

@ EN: None learned
Text_ExskillDesc_00:: @ 0x0837454E
Str_1AAE:
.if ENGLISH
	.string "None learned$"
.else
	.string "おぼえていない$"
.endif

@ EN: BUSTER SHOT / Reflects off / of walls.
Text_ExskillDesc_01:: @ 0x08374556
Str_1AB6:
.if ENGLISH
	.string "{RED}BUSTER SHOT{RED_END}\n"
	.string "Reflects off\n"
	.string "of walls.$"
.else
	.string "{RED}バスターショット{RED_END}\n"
	.string "かべやゆかにあたると\n"
	.string "はんしゃする$"
.endif

@ EN: BUSTER SHOT / Splits shot / when used / with Thunder / Body Chip.
Text_ExskillDesc_02:: @ 0x08374573
Str_1AD3:
.if ENGLISH
	.string "{RED}BUSTER SHOT{RED_END}\n"
	.string "Splits shot\n"
	.string "when used\n"
	.string "with Thunder\n"
	.string "Body Chip.$"
.else
	.string "{RED}バスターショット{RED_END}\n"
	.string "ボディチップを\n"
	.string "サンダーにして使うと\n"
	.string "上下にわかれたショットを\n"
	.string "うつことができる$"
.endif

@ EN: BUSTER SHOT / Explodes / when used / with Flame / Body Chip.
Text_ExskillDesc_03:: @ 0x083745AA
Str_1B0A:
.if ENGLISH
	.string "{RED}BUSTER SHOT{RED_END}\n"
	.string "Explodes\n"
	.string "when used\n"
	.string "with Flame\n"
	.string "Body Chip.$"
.else
	.string "{RED}バスターショット{RED_END}\n"
	.string "ボディチップを\n"
	.string "フレイムにして使うと\n"
	.string "バクフウで テキを\n"
	.string "まきこむことができる$"
.endif

@ EN: BUSTER SHOT / Shoots ice / when used / with Ice / Body Chip.
Text_ExskillDesc_04:: @ 0x083745DE
Str_1B3E:
.if ENGLISH
	.string "{RED}BUSTER SHOT{RED_END}\n"
	.string "Shoots ice\n"
	.string "when used\n"
	.string "with Ice\n"
	.string "Body Chip.$"
.else
	.string "{RED}バスターショット{RED_END}\n"
	.string "ボディチップを\n"
	.string "アイスにして使うと\n"
	.string "コオリのヤイバが\n"
	.string "とんでいく$"
.endif

@ EN: Z SABER / Skewer foes / by dashing / with saber.
Text_ExskillDesc_05:: @ 0x0837460B
Str_1B6B:
.if ENGLISH
	.string "{RED}Z SABER{RED_END}\n"
	.string "Skewer foes\n"
	.string "by dashing\n"
	.string "with saber.$"
.else
	.string "{RED}ゼットセイバー{RED_END}\n"
	.string "ダッシュをしながら\n"
	.string "セイバーでコウゲキすると\n"
	.string "テキをつきさす$"
.endif

@ EN: Z SABER / Press Down / and slash / during fall / or slide to / skewer foes / bel
Text_ExskillDesc_06:: @ 0x08374634
Str_1B94:
.if ENGLISH
	.string "{RED}Z SABER{RED_END}\n"
	.string "Press Down\n"
	.string "and slash\n"
	.string "during fall\n"
	.string "or slide to\n"
	.string "skewer foes\n"
	.string "below.$"
.else
	.string "{RED}ゼットセイバー{RED_END}\n"
	.string "ジャンプ中や らっか中に\n"
	.string "✚ボタンの下を\n"
	.string "おしながら\n"
	.string "セイバーでコウゲキすると\n"
	.string "真下にいるテキを\n"
	.string "つきさすことができる$"
.endif

@ EN: Z SABER / Press Up and / use Saber / to slice / upward.
Text_ExskillDesc_07:: @ 0x08374680
Str_1BE0:
.if ENGLISH
	.string "{RED}Z SABER{RED_END}\n"
	.string "Press Up and\n"
	.string "use Saber\n"
	.string "to slice\n"
	.string "upward.$"
.else
	.string "{RED}ゼットセイバー{RED_END}\n"
	.string "✚ボタンの上を\n"
	.string "おしながら\n"
	.string "セイバーでコウゲキすると\n"
	.string "ジャンプできりあげる$"
.endif

@ EN: Z SABER / Press Down / and slash / to shoot a / blade ahead.
Text_ExskillDesc_08:: @ 0x083746B2
Str_1C12:
.if ENGLISH
	.string "{RED}Z SABER{RED_END}\n"
	.string "Press Down\n"
	.string "and slash\n"
	.string "to shoot a\n"
	.string "blade ahead.$"
.else
	.string "{RED}ゼットセイバー{RED_END}\n"
	.string "✚ボタンの下を\n"
	.string "おしながら\n"
	.string "セイバーでコウゲキすると\n"
	.string "前方にヤイバがとんでいく$"
.endif

@ EN: RECOIL ROD / Rapidly use / Rod for / multi atk.
Text_ExskillDesc_09:: @ 0x083746E8
Str_1C48:
.if ENGLISH
	.string "{RED}RECOIL ROD{RED_END}\n"
	.string "Rapidly use\n"
	.string "Rod for\n"
	.string "multi atk.$"
.else
	.string "{RED}リコイルロッド{RED_END}\n"
	.string "ロッドをレンダすると\n"
	.string "前方にレンゾクで\n"
	.string "コウゲキができる$"
.endif

@ EN: RECOIL ROD / Press Up and / charge Rod / to shoot / above.
Text_ExskillDesc_10:: @ 0x08374711
Str_1C71:
.if ENGLISH
	.string "{RED}RECOIL ROD{RED_END}\n"
	.string "Press Up and\n"
	.string "charge Rod\n"
	.string "to shoot\n"
	.string "above.$"
.else
	.string "{RED}リコイルロッド{RED_END}\n"
	.string "✚ボタンの上を\n"
	.string "おしながら ロッドを\n"
	.string "チャージでコウゲキすると\n"
	.string "上に向けて タマをうてる$"
.endif

@ EN: S.BOOMERANG / S.Boomerang / skims the / ground.
Text_ExskillDesc_11:: @ 0x0837474C
Str_1CAC:
.if ENGLISH
	.string "{RED}S.BOOMERANG{RED_END}\n"
	.string "S.Boomerang\n"
	.string "skims the\n"
	.string "ground.$"
.else
	.string "{RED}シールドブーメラン{RED_END}\n"
	.string "地形にそって\n"
	.string "シールドブーメランが\n"
	.string "とんでいく$"
.endif

@ EN: S.BOOMERANG / Press Down / and use S. / Boomerang / to form a / shield.
Text_ExskillDesc_12:: @ 0x08374772
Str_1CD2:
.if ENGLISH
	.string "{RED}S.BOOMERANG{RED_END}\n"
	.string "Press Down\n"
	.string "and use S.\n"
	.string "Boomerang\n"
	.string "to form a \n"
	.string "shield.$"
.else
	.string "{RED}シールドブーメラン{RED_END}\n"
	.string "✚ボタンの下を\n"
	.string "おしながら\n"
	.string "シールドブーメランを\n"
	.string "なげると 自分のまわりを\n"
	.string "シールドがまわる$"
.endif

@ EN: None learned
Text_ExskillDesc_13:: @ 0x083747B1
Str_1D11:
.if ENGLISH
	.string "None learned\n"
	.string "$"
.else
	.string "おぼえていない\n"
	.string "$"
.endif

@ EN: Press A BUTTON to analyze.
sDiskAnalysisGuide:: @ 0x083747ba
Str_1D1A:
.if ENGLISH
  .string "Press A BUTTON to analyze.$"
.else
  .string "✚ボタンでえらんで Aボタンでカイセキできます$"
.endif
Str_1D33:
.if ENGLISH
  .string "Press B BUTTON to end.$"
.else
  .string "Bボタンでしゅうりょうします$"
.endif
Str_1D42:
.if ENGLISH
  .string "No.$"
.else
  .string "NO.$"
.endif
Str_1D46:
.if ENGLISH
  .string "This disk\n"
  .string "is unread.$"
.else
  .string "このディスクは\nカイセキされていません$"
.endif

@ EN: \xF7 NEW GAME
sTitleMenu:: @ 0x083747fa
Str_1D5A:
.if ENGLISH
  .string "{F7 0x00}NEW GAME$"
.else
  .string "{F7 0x00}はじめから$"
.endif
Str_1D62:
.if ENGLISH
  .string "{F7 0x01}NEW GAME$"
.else
  .string "{F7 0x01}はじめから$"
.endif
Str_1D6A:
.if ENGLISH
  .string "{F7 0x00}LOAD GAME$"
.else
  .string "{F7 0x00}つづきから$"
.endif
Str_1D72:
.if ENGLISH
  .string "{F7 0x01}LOAD GAME$"
.else
  .string "{F7 0x01}つづきから$"
.endif
Str_1D7A:
.if ENGLISH
  .string "{F7 0x00}MINI GAMES$"
.else
  .string "{F7 0x00}ミニゲーム$"
.endif
Str_1D82:
.if ENGLISH
  .string "{F7 0x01}MINI GAMES$"
.else
  .string "{F7 0x01}ミニゲーム$"
.endif

@ EN: \xF74PLEASE WAIT...
sConnections_0:: @ 0x0837482a
Str_1D8A:
.if ENGLISH
  .string "{F7 0x05}PLEASE WAIT...$"
.else
  .string "{F7 0x05}つうしん まちうけちゅう$"
.endif
@ EN: \xF7 B BUTTON: CANCEL
sConnections_1:: @ 0x08374839
Str_1D99:
.if ENGLISH
  .string "{F7 0x00}B BUTTON: CANCEL$"
.else
  .string "{F7 0x00}Bボタンでキャンセル$"
.endif
@ EN: \xF74 Exe 4 is / \xF74selecting chip.
sConnections_2:: @ 0x08374846
Str_1DA6:
.if ENGLISH
  .string "{F7 0x05}    Exe 4 is\n"
  .string "{F7 0x05}selecting chip.$"
.else
  .string "{F7 0x05}    エグゼ4が\n{F7 0x05}チップをせんたくちゅうです$"
.endif
@ EN: \xF73LINK / TERMINATED.
sConnections_3:: @ 0x08374862
Str_1DC2:
.if ENGLISH
  .string "{F7 0x04}LINK\n"
  .string "TERMINATED.$"
.else
  .string "{F7 0x04}つうしんエラーが\nはっせいしました$"
.endif

@ EN: \xF7 CONTINUE
sGameOver:: @ 0x08374876
Str_1DD6:
.if ENGLISH
  .string " {F7 0x00}   CONTINUE$"
.else
  .string "{F7 0x00}    コンティニュー$"
.endif
Str_1DE4:
.if ENGLISH
  .string " {F7 0x01}   CONTINUE$"
.else
  .string "{F7 0x01}    コンティニュー$"
.endif
Str_1DF2:
.if ENGLISH
  .string " {F7 0x00}RESTART{RED_END} {F7 0x00}S.{RED_END} {F7 0x00}GAME$"
.else
  .string " {F7 0x00}セーブした場所からやりなおす$"
.endif
Str_1E04:
.if ENGLISH
  .string " {F7 0x01}RESTART{RED_END} {F7 0x01}S.{RED_END} {F7 0x01}GAME$"
.else
  .string " {F7 0x01}セーブした場所からやりなおす$"
.endif
Str_1E16:
.if ENGLISH
  .string "{F7 0x00} QUIT THE GAME$"
.else
  .string "{F7 0x00}    ゲームをやめる$"
.endif
Str_1E24:
.if ENGLISH
  .string "{F7 0x01} QUIT THE GAME$"
.else
  .string "{F7 0x01}    ゲームをやめる$"
.endif

@ EN: \xF7 ZERO
sMiniGameNames:: @ 0x083748d2
Str_1E32:
.if ENGLISH
  .string " {F7 0x00}  ZERO$"
.else
  .string " {F7 0x00}  ゼロ$"
.endif
Str_1E3A:
.if ENGLISH
  .string " {F7 0x01}  ZERO$"
.else
  .string " {F7 0x01}  ゼロ$"
.endif
Str_1E42:
.if ENGLISH
  .string " {F7 0x00}  CIEL$"
.else
  .string "{F7 0x00}  シエル$"
.endif
Str_1E4A:
.if ENGLISH
  .string " {F7 0x01}  CIEL$"
.else
  .string "{F7 0x01}  シエル$"
.endif
Str_1E52:
.if ENGLISH
  .string " {F7 0x00} COPY X$"
.else
  .string "{F7 0x00}コピーエックス$"
.endif
Str_1E5C:
.if ENGLISH
  .string " {F7 0x01} COPY X$"
.else
  .string "{F7 0x01}コピーエックス$"
.endif
Str_1E66:
.if ENGLISH
  .string "{F7 0x00} HARPUIA$"
.else
  .string " {F7 0x00}ハルピュイア$"
.endif
Str_1E70:
.if ENGLISH
  .string "{F7 0x01} HARPUIA$"
.else
  .string " {F7 0x01}ハルピュイア$"
.endif
Str_1E7A:
.if ENGLISH
  .string " {F7 0x00} FEFNIR$"
.else
  .string " {F7 0x00}ファーブニル$"
.endif
Str_1E84:
.if ENGLISH
  .string " {F7 0x01} FEFNIR$"
.else
  .string " {F7 0x01}ファーブニル$"
.endif
Str_1E8E:
.if ENGLISH
  .string "{F7 0x00}LEVIATHAN$"
.else
  .string " {F7 0x00}レヴィアタン$"
.endif
Str_1E98:
.if ENGLISH
  .string "{F7 0x01}LEVIATHAN$"
.else
  .string " {F7 0x01}レヴィアタン$"
.endif
Str_1EA2:
.if ENGLISH
  .string "{F7 0x00} PHANTOM$"
.else
  .string "{F7 0x00} ファントム$"
.endif
Str_1EAB:
.if ENGLISH
  .string "{F7 0x01} PHANTOM$"
.else
  .string "{F7 0x01} ファントム$"
.endif

# size is 1516 bytes
@ EN: STAFF / / / / / DIRECTOR / RYOTA ITO / YOSHINORI KAWANO / / / GAME DESIGNER / YO
sStaffRoll:: @ 0x08374954
  .include "src/data/strings/staff_roll.inc"

@ EN: AUTO-CHARGE / (Head Chip) / / Automatic / charge to / your weapon.
sDiskContents:: @ 0x08374f40
  .include "src/data/strings/disk.inc"

@ EN: 000
sDiskNumbers:: @ 0x08375f5e
  .include "src/data/strings/disk_number.inc"

@ EN: Dr. Weil
sSubmergedLibFileNames:: @ 0x0837639c
Str_38FC:
.if ENGLISH
  .string "Dr. Weil$"
.else
  .string "バイルのデータ$"
.endif
Str_3904:
.if ENGLISH
  .string "Omega$"
.else
  .string "オメガのデータ$"
.endif
Str_390C:
.if ENGLISH
  .string "Dark Elf$"
.else
  .string "ダークエルフのデータ$"
.endif
Str_3917:
.if ENGLISH
  .string "Elf Wars$"
.else
  .string "ヨウセイ戦争のデータ$"
.endif

@ size is 996 bytes
@ EN: RULES
Text_MiniGameRules:: @ 0x083763c4
Str_3924:
.if ENGLISH
  .string "{RED}RULES{RED_END}$"
.else
  .string "{RED}ルール{RED_END}$"
.endif

@ EN: Aim with +Control Pad and / use B BUTTON to hit / Mellnets with Recoil Rod. / Di
Text_MinigameDesc_Zero::
Str_392A:
.if ENGLISH
	.string "Aim with +Control Pad and\n"
	.string "use B BUTTON to hit\n"
	.string "Mellnets with Recoil Rod.\n"
	.string "Different colored Mellnets\n"
	.string "are harder and require 2\n"
	.string "shots or a charged shot.\n"
	.string "3 misses = game over.$"
.else
	.string "6方向から とんでくる メルネットを\n"
	.string "✚ボタンで ねらいをさだめ、\n"
	.string "Bボタンのリコイルロッドで コウゲキします。\n"
	.string "いろのちがう メルネットは、かたいので\n"
	.string "2ヒットさせるか、チャージこうげきで、\n"
	.string "ふきとばさなくてはいけません。\n"
	.string "3回ミスをすると ゲームオーバーです。$"
.endif

@ EN: Guide 5 colored jewels to / the right colored beaker. / The jewels will take all
Text_MinigameDesc_Ciel::
Str_39B3:
.if ENGLISH
	.string "Guide 5 colored jewels to\n"
	.string "the right colored beaker.\n"
	.string "The jewels will take all\n"
	.string "possible turns.\n"
	.string "Use A BUTTON or B BUTTON\n"
	.string "to open or close paths.\n"
	.string "3 misses = game over.$"
.else
	.string "上から おちてくる 5しょくのジュエルを\n"
	.string "ただしい いろのビーカーへと みちびきます。\n"
	.string "ジュエルの とおりみちに、よこの あなが\n"
	.string "あいている ばあいは、そちらに行きます。\n"
	.string "AボタンかBボタンで とおりみちに フタをしたり\n"
	.string "外したりして、うまく ゆうどうしてください。\n"
	.string "3回ミスをすると ゲームオーバーです。$"
.endif

@ EN: Using 3 elements, destroy / panels on a belt conveyor. / The L BUTTON and R BUTT
Text_MinigameDesc_X::
Str_3A51:
.if ENGLISH
	.string "Using 3 elements, destroy\n"
	.string "panels on a belt conveyor.\n"
	.string "The L BUTTON and R BUTTON\n"
	.string "change elements, B BUTTON\n"
	.string "attacks. Thunder on Ice,\n"
	.string "Ice on Fire, Fire on Thun-\n"
	.string "der. 3 misses = game over.$"
.else
	.string "サンダー・フレイム・アイスのエレメントを\n"
	.string "きりかえて、ベルトコンベアをながれてくるパネルを\n"
	.string "ハカイしてください。Lボタン・Rボタンで\n"
	.string "エレメントをきりかえて、Bボタンでコウゲキします。\n"
	.string "サンダーはアイス、アイスはフレイム、フレイムは\n"
	.string "サンダーのコウゲキでハカイできます。\n"
	.string "3回ミスをすると ゲームオーバーです。$"
.endif

@ EN: Riding Aztec Falcon jump / over obstacles and slash / foes. A BUTTON to jump\xED
Text_MinigameDesc_Harpuia::
Str_3AEE:
.if ENGLISH
	.string "Riding Aztec Falcon jump\n"
	.string "over obstacles and slash\n"
	.string "foes. A BUTTON to jump{0xED}\n"
	.string "B BUTTON to slash. Ends\n"
	.string "when you get hit 3 times,\n"
	.string "crash, or fall in a pit.$"
.else
	.string "アステファルコンにのり、しょうがいぶつを\n"
	.string "ジャンプでとびこえ、\n"
	.string "テキをブレードで コウゲキします。\n"
	.string "Aボタンでジャンプ、Bボタンでコウゲキです。\n"
	.string "しょうがいぶつやテキに3回当たるか、はさまれたり\n"
	.string "あなにおちたりすると ゲームオーバーです。$"
.endif

@ EN: Stop Carryarms from taking / the items. +Control Pad / to move Fefnir\xED B BUTT
Text_MinigameDesc_Fefnir::
Str_3B68:
.if ENGLISH
	.string "Stop Carryarms from taking\n"
	.string "the items. +Control Pad \n"
	.string "to move Fefnir{0xED} B BUTTON\n"
	.string "to fire Meteor Rain. Score\n"
	.string "bonus points when items\n"
	.string "Drop.Game ends when an\n"
	.string "item is taken.$"
.else
	.string "キャリアームに ブッシをうばわれないように\n"
	.string "✚ボタンで左右にファーブニルを動かし、\n"
	.string "Bボタンでメテオレインを上にハッシャします。\n"
	.string "ブッシをもったキャリアームを高いイチで たおすと\n"
	.string "ブッシがおちるまでの間、とくてんが入ります。\n"
	.string "ブッシが 1つでも エリアの外に\n"
	.string "もっていかれてしまうと、ゲームオーバーです。$"
.endif

@ EN: Move Leviathan w/ +Control / Pad\xED B BUTTON for spear. / Earn score and time b
Text_MinigameDesc_Leviathan::
Str_3C0A:
.if ENGLISH
	.string "Move Leviathan w/ +Control\n"
	.string "Pad{0xED} B BUTTON for spear.\n"
	.string "Earn score and time by\n"
	.string "hitting only Mechaniloids.\n"
	.string "Consecutive hits score\n"
	.string "bonus points. Game ends \n"
	.string "when time runs out.$"
.else
	.string "✚ボタンでレヴィアタンを左右に動かし、\n"
	.string "Bボタンでスピアを下につきます。\n"
	.string "うみの生きものをころさないように\n"
	.string "うまく メカニロイドだけをたおして、\n"
	.string "スコアとタイムをかせいでください。\n"
	.string "のがさずレンゾクでつくと 高とくてんです。\n"
	.string "タイムが0になると ゲームオーバーです。$"
.endif

@ EN: Jump from one shuriken to / another. +Control Pad to / move\xED A BUTTON to jump
Text_MinigameDesc_Phantom::
Str_3C97:
.if ENGLISH
	.string "Jump from one shuriken to\n"
	.string "another. +Control Pad to\n"
	.string "move{0xED} A BUTTON to jump. \n"
	.string "Ends when hit 3 times, or\n"
	.string "you fall from a shuriken.$"
.else
	.string "シュリケンからシュリケンへと おちないように\n"
	.string "✚ボタンでファントムを左右に動かしながら\n"
	.string "Aボタンでジャンプして とびうつります。\n"
	.string "しょうがいぶつに3回当たるか、シュリケンから\n"
	.string "おちてしまうと ゲームオーバーです。$"
.endif
