#include <criterion/criterion.h>
#define NSS_OCTOPASS_CONFIG_FILE "example.octopass.conf"

#include "nss_octopass.h"
#include "nss_octopass.c"
#include "nss_octopass-passwd.c"

Test(nss_octopass, getpwnam_r)
{
  enum nss_status status;
  struct passwd pwent;
  int err;
  int buflen = 2048;
  char buf[buflen];

  const char *name = "linyows";
  status           = _nss_octopass_getpwnam_r(name, &pwent, buf, buflen, &err);

  cr_assert_eq(err, 0);
  cr_assert_eq(status, NSS_STATUS_SUCCESS);
  cr_assert_str_eq(pwent.pw_name, "linyows");
  cr_assert_str_eq(pwent.pw_passwd, "x");
  cr_assert_eq(pwent.pw_uid, 74049);
  cr_assert_eq(pwent.pw_gid, 2000);
  cr_assert_str_eq(pwent.pw_gecos, "managed by nss-octopass");
  cr_assert_str_eq(pwent.pw_dir, "/home/linyows");
  cr_assert_str_eq(pwent.pw_shell, "/bin/bash");
}

Test(nss_octopass, getpwnam_r__returns_not_found_if_it_is_not_team_member)
{
  enum nss_status status;
  struct passwd pwent;
  int err;
  int buflen = 2048;
  char buf[buflen];

  const char *name = "linyowsno";
  status           = _nss_octopass_getpwnam_r(name, &pwent, buf, buflen, &err);

  cr_assert_eq(err, ENOENT);
  cr_assert_eq(status, NSS_STATUS_NOTFOUND);
}

Test(nss_octopass, pwent)
{
}