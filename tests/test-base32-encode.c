#include <stdio.h>
#include <criterion/criterion.h>
#include "../src/baseencode.h"


Test(b32_encode_test, null_input) {
    const char *k = NULL;

    char *ek = base32_encode(k, 5);

    cr_expect_null(ek, "%s");
}


Test(b32_encode_test, data_nodata_size_nosize) {
    const char *k1 = "";
    const char *k2 = "asdiasjdijis";

    // test no-data with given size, data with no-size and no-data no-size
    char *ek1 = base32_encode(k1, 30);
    char *ek2 = base32_encode(k2, 0);

    cr_expect(strcmp(k1, ek1) == 0, "Expected %s to be equal to %s", ek1, k1);
    cr_expect_null(ek2, "%s");

    free(ek1);
}


Test(b32_encode_test, b32_all_chars) {
    const char *k = "ADFG413!£$%&&((/?^çé*[]#)-.,|<>+";
    const char *k_enc = "IFCEMRZUGEZSDQVDEQSSMJRIFAXT6XWDU7B2SKS3LURSSLJOFR6DYPRL";

    char *ek = base32_encode(k, strlen(k)+1);

    cr_expect(strcmp(ek, k_enc) == 0, "Expected %s to be equal to %s", ek, k_enc);

    free(ek);
}


Test(b32_encode_test, b32_all_chars_noplusone) {
    const char *k = "ADFG413!£$%&&((/?^çé*[]#)-.,|<>+";
    const char *k_enc = "IFCEMRZUGEZSDQVDEQSSMJRIFAXT6XWDU7B2SKS3LURSSLJOFR6DYPRL";

    char *ek = base32_encode(k, strlen(k));

    cr_expect(strcmp(ek, k_enc) == 0, "Expected %s to be equal to %s", ek, k_enc);

    free(ek);
}


Test(b32_encode_test, b32_rfc4648) {
    const char *k[] = {"", "f", "fo", "foo", "foob", "fooba", "foobar"};
    const char *k_enc[] = {"", "MY======", "MZXQ====", "MZXW6===", "MZXW6YQ=", "MZXW6YTB", "MZXW6YTBOI======"};

    for (int i = 0; i < 7; i++) {
        char *ek = base32_encode(k[i], strlen(k[i])+1);
        cr_expect(strcmp(ek, k_enc[i]) == 0, "Expected %s to be equal to %s", ek, k_enc[i]);
        free(ek);
    }
}


Test(b32_encode_test, b32_rfc4648_noplusone) {
    const char *k[] = {"", "f", "fo", "foo", "foob", "fooba", "foobar"};
    const char *k_enc[] = {"", "MY======", "MZXQ====", "MZXW6===", "MZXW6YQ=", "MZXW6YTB", "MZXW6YTBOI======"};

    for (int i = 0; i < 7; i++) {
        char *ek = base32_encode(k[i], strlen(k[i]));
        cr_expect(strcmp(ek, k_enc[i]) == 0, "Expected %s to be equal to %s", ek, k_enc[i]);
        free(ek);
    }
}


Test(b32_encode_test, b32_encode_input_exceeded) {
    const char *k = "test";
    size_t len = 65*1024*1024;

    char *ek = base32_encode(k, len);
    cr_expect_null(ek, "%s");
}