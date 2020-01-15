#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>

#include "Util.h"

static int errors = 0;

int test(const char *method_name, const char *method_sig, const char *expected, int expected_param_count)
{
  std::string a;
  std::string b;
  int param_count;

  a = method_name;
  b = method_sig;

  //strcpy(a, method_name);
  //strcpy(b, method_sig);

  Util::method_sanitize(a, b, param_count);

  if (a != expected)
  {
    printf("Error: method=%s%s\n"
           "     expected=%s\n"
           "       output=%s\n",
      method_name, method_sig, expected, a.c_str());
    errors++;
    return -1;
  }

  if (expected_param_count != param_count)
  {
    printf("Error: method=%s%s\n"
           "     expected=%d\n"
           "  param_count=%d\n",
      method_name, method_sig, expected_param_count, param_count);
    errors++;
    return -1;
  }

  return 0;
}

int main(int argc, char *argv[])
{
  test("BillionDevices_run", "()V", "BillionDevices_run", 0);
  test("Credits_run", "()V", "Credits_run", 0);
  test("Cubes_run", "()V", "Cubes_run", 0);
  test("Logos_run", "()V", "Logos_run", 0);
  test("Mandelbrots_renderMandelbrot", "(IFFFF)V", "Mandelbrots_renderMandelbrot_IFFFF", 5);
  test("Mandelbrots_downloadMandelbrot", "(ILnet/mikekohn/java_grinder/Draw3D/Texture16;)V", "Mandelbrots_downloadMandelbrot_ILnet_mikekohn_java_grinder_Draw3D_Texture16_", 2);
  test("Mandelbrots_run", "()V", "Mandelbrots_run", 0);
  test("SquareRing_drawRing", "(Lnet/mikekohn/java_grinder/Draw3D/TriangleFan;IIIFI)V", "SquareRing_drawRing_Lnet_mikekohn_java_grinder_Draw3D_TriangleFan_IIIFI", 6);
  test("SquareRing_run", "()V", "SquareRing_run", 0);
  test("Stars_animateStars", "([SLnet/mikekohn/java_grinder/Draw3D/Points;)V", "Stars_animateStars_aSLnet_mikekohn_java_grinder_Draw3D_Points_", 2);
  test("Stars_run", "()V", "Stars_run", 0);
  test("add_letters", "(Ljava/lang/String;)I", "add_letters_X", 1);

  return errors == 0 ? 0 : -1;
}

