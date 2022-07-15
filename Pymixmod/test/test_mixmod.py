# import mixmod as mymod
from __future__ import absolute_import, division, print_function, unicode_literals

import unittest

import pandas as pnd

import mixmod
from mixmod import gm

# mixmodGaussianModel()
raw_gaussian_all = """Gaussian_pk_L_I Gaussian_pk_Lk_I Gaussian_pk_L_B Gaussian_pk_Lk_B Gaussian_pk_L_Bk Gaussian_pk_Lk_Bk Gaussian_pk_L_C Gaussian_pk_Lk_C Gaussian_pk_L_D_Ak_D Gaussian_pk_Lk_D_Ak_D Gaussian_pk_L_Dk_A_Dk Gaussian_pk_Lk_Dk_A_Dk Gaussian_pk_L_Ck Gaussian_pk_Lk_Ck Gaussian_p_L_I Gaussian_p_Lk_I Gaussian_p_L_B Gaussian_p_Lk_B Gaussian_p_L_Bk Gaussian_p_Lk_Bk Gaussian_p_L_C Gaussian_p_Lk_C Gaussian_p_L_D_Ak_D Gaussian_p_Lk_D_Ak_D Gaussian_p_L_Dk_A_Dk Gaussian_p_Lk_Dk_A_Dk Gaussian_p_L_Ck Gaussian_p_Lk_Ck"""

# mixmodGaussianModel(family="spherical")
raw_gaussian_spherical = "Gaussian_pk_L_I Gaussian_pk_Lk_I Gaussian_p_L_I Gaussian_p_Lk_I"

# mixmodGaussianModel(family="diagonal")
raw_gaussian_diagonal = """Gaussian_pk_L_B Gaussian_pk_Lk_B Gaussian_pk_L_Bk Gaussian_pk_Lk_Bk Gaussian_p_L_B Gaussian_p_Lk_B Gaussian_p_L_Bk Gaussian_p_Lk_Bk"""
# mixmodGaussianModel(family="general")
raw_gaussian_general = """Gaussian_pk_L_C Gaussian_pk_Lk_C Gaussian_pk_L_D_Ak_D Gaussian_pk_Lk_D_Ak_D Gaussian_pk_L_Dk_A_Dk Gaussian_pk_Lk_Dk_A_Dk Gaussian_pk_L_Ck Gaussian_pk_Lk_Ck Gaussian_p_L_C Gaussian_p_Lk_C Gaussian_p_L_D_Ak_D Gaussian_p_Lk_D_Ak_D Gaussian_p_L_Dk_A_Dk Gaussian_p_Lk_Dk_A_Dk Gaussian_p_L_Ck Gaussian_p_Lk_Ck"""

# mixmodGaussianModel(family=c("spherical","diagonal"))
raw_gaussian_spherical_diagonal = """Gaussian_pk_L_I Gaussian_pk_Lk_I Gaussian_p_L_I Gaussian_p_Lk_I Gaussian_pk_L_B Gaussian_pk_Lk_B Gaussian_pk_L_Bk Gaussian_pk_Lk_Bk Gaussian_p_L_B Gaussian_p_Lk_B Gaussian_p_L_Bk Gaussian_p_Lk_Bk"""

# mixmodGaussianModel(equal.proportions=F)
raw_gaussian_free_proportions = """Gaussian_pk_L_I Gaussian_pk_Lk_I Gaussian_pk_L_B Gaussian_pk_Lk_B Gaussian_pk_L_Bk Gaussian_pk_Lk_Bk Gaussian_pk_L_C Gaussian_pk_Lk_C Gaussian_pk_L_D_Ak_D Gaussian_pk_Lk_D_Ak_D Gaussian_pk_L_Dk_A_Dk Gaussian_pk_Lk_Dk_A_Dk Gaussian_pk_L_Ck Gaussian_pk_Lk_Ck"""

# mixmodGaussianModel(free.proportions=F)
raw_gaussian_equal_proportions = """Gaussian_p_L_I Gaussian_p_Lk_I Gaussian_p_L_B Gaussian_p_Lk_B Gaussian_p_L_Bk Gaussian_p_Lk_Bk Gaussian_p_L_C Gaussian_p_Lk_C Gaussian_p_L_D_Ak_D Gaussian_p_Lk_D_Ak_D Gaussian_p_L_Dk_A_Dk Gaussian_p_Lk_Dk_A_Dk Gaussian_p_L_Ck Gaussian_p_Lk_Ck"""

# mixmodMultinomialModel()
raw_multinomial_all = "Binary_pk_E Binary_pk_Ekj Binary_pk_Ekjh Binary_pk_Ej Binary_pk_Ek Binary_p_E Binary_p_Ekj Binary_p_Ekjh Binary_p_Ej Binary_p_Ek"

# mixmodMultinomialModel(free.proportions=F)
raw_multinomial_equal_proportions = "Binary_p_E Binary_p_Ekj Binary_p_Ekjh Binary_p_Ej Binary_p_Ek"

# mixmodMultinomialModel(equal.proportions=F)
raw_multinomial_free_proportions = "Binary_pk_E Binary_pk_Ekj Binary_pk_Ekjh Binary_pk_Ej Binary_pk_Ek"

# mixmodMultinomialModel(variable.independency=T)
raw_multinomial_var_indep_true = "Binary_pk_E Binary_pk_Ek Binary_p_E Binary_p_Ek"

# mixmodMultinomialModel(variable.independency=F)
raw_multinomial_var_indep_false = "Binary_pk_Ekj Binary_pk_Ekjh Binary_pk_Ej Binary_p_Ekj Binary_p_Ekjh Binary_p_Ej"

# mixmodMultinomialModel(component.independency=T)
raw_multinomial_comp_indep_true = "Binary_pk_E Binary_pk_Ej Binary_p_E Binary_p_Ej"

# mixmodMultinomialModel(component.independency=F)
raw_multinomial_comp_indep_false = "Binary_pk_Ekj Binary_pk_Ekjh Binary_pk_Ek Binary_p_Ekj Binary_p_Ekjh Binary_p_Ek"

# mixmodMultinomialModel(component.independency=F, variable.independency=T)
raw_multinomial_ci_f_vi_t = "Binary_pk_Ek Binary_p_Ek"

# mixmodMultinomialModel(component.independency=T, variable.independency=F)
raw_multinomial_ci_t_vi_f = "Binary_pk_Ej Binary_p_Ej"

# mixmodMultinomialModel(component.independency=T, equal.proportions=F)
raw_multinomial_ci_t_eqp_f = "Binary_pk_E Binary_pk_Ej"

# mixmodMultinomialModel(component.independency=F, free.proportions=F)
raw_multinomial_ci_f_eqp_t = "Binary_p_Ekj Binary_p_Ekjh Binary_p_Ek"

# mixmodMultinomialModel(equal.proportions=T, free.proportions=F)
raw_multinomial_eqp_t_frp_f = "Binary_p_E Binary_p_Ekj Binary_p_Ekjh Binary_p_Ej Binary_p_Ek"

# mixmodMultinomialModel(equal.proportions=F, free.proportions=T)
raw_multinomial_eqp_f_frp_t = "Binary_pk_E Binary_pk_Ekj Binary_pk_Ekjh Binary_pk_Ej Binary_pk_Ek"

#
# Composite stuff
#

# mixmodCompositeModel()
raw_composite_all = """Heterogeneous_pk_E_L_B Heterogeneous_pk_E_Lk_B Heterogeneous_pk_E_L_Bk Heterogeneous_pk_E_Lk_Bk Heterogeneous_pk_Ekj_L_B Heterogeneous_pk_Ekj_Lk_B Heterogeneous_pk_Ekj_L_Bk Heterogeneous_pk_Ekj_Lk_Bk Heterogeneous_pk_Ekjh_L_B Heterogeneous_pk_Ekjh_Lk_B Heterogeneous_pk_Ekjh_L_Bk Heterogeneous_pk_Ekjh_Lk_Bk Heterogeneous_pk_Ej_L_B Heterogeneous_pk_Ej_Lk_B Heterogeneous_pk_Ej_L_Bk Heterogeneous_pk_Ej_Lk_Bk Heterogeneous_pk_Ek_L_B Heterogeneous_pk_Ek_Lk_B Heterogeneous_pk_Ek_L_Bk Heterogeneous_pk_Ek_Lk_Bk Heterogeneous_p_E_L_B Heterogeneous_p_E_Lk_B Heterogeneous_p_E_L_Bk Heterogeneous_p_E_Lk_Bk Heterogeneous_p_Ekj_L_B Heterogeneous_p_Ekj_Lk_B Heterogeneous_p_Ekj_L_Bk Heterogeneous_p_Ekj_Lk_Bk Heterogeneous_p_Ekjh_L_B Heterogeneous_p_Ekjh_Lk_B Heterogeneous_p_Ekjh_L_Bk Heterogeneous_p_Ekjh_Lk_Bk Heterogeneous_p_Ej_L_B Heterogeneous_p_Ej_Lk_B Heterogeneous_p_Ej_L_Bk Heterogeneous_p_Ej_Lk_Bk Heterogeneous_p_Ek_L_B Heterogeneous_p_Ek_Lk_B Heterogeneous_p_Ek_L_Bk Heterogeneous_p_Ek_Lk_Bk"""

# mixmodCompositeModel(free.proportions=F)
raw_composite_equal_proportions = """Heterogeneous_p_E_L_B Heterogeneous_p_E_Lk_B Heterogeneous_p_E_L_Bk Heterogeneous_p_E_Lk_Bk Heterogeneous_p_Ekj_L_B Heterogeneous_p_Ekj_Lk_B Heterogeneous_p_Ekj_L_Bk Heterogeneous_p_Ekj_Lk_Bk Heterogeneous_p_Ekjh_L_B Heterogeneous_p_Ekjh_Lk_B Heterogeneous_p_Ekjh_L_Bk Heterogeneous_p_Ekjh_Lk_Bk Heterogeneous_p_Ej_L_B Heterogeneous_p_Ej_Lk_B Heterogeneous_p_Ej_L_Bk Heterogeneous_p_Ej_Lk_Bk Heterogeneous_p_Ek_L_B Heterogeneous_p_Ek_Lk_B Heterogeneous_p_Ek_L_Bk Heterogeneous_p_Ek_Lk_Bk"""

# mixmodCompositeModel(equal.proportions=F)
raw_composite_free_proportions = """Heterogeneous_pk_E_L_B Heterogeneous_pk_E_Lk_B Heterogeneous_pk_E_L_Bk Heterogeneous_pk_E_Lk_Bk Heterogeneous_pk_Ekj_L_B Heterogeneous_pk_Ekj_Lk_B Heterogeneous_pk_Ekj_L_Bk Heterogeneous_pk_Ekj_Lk_Bk Heterogeneous_pk_Ekjh_L_B Heterogeneous_pk_Ekjh_Lk_B Heterogeneous_pk_Ekjh_L_Bk Heterogeneous_pk_Ekjh_Lk_Bk Heterogeneous_pk_Ej_L_B Heterogeneous_pk_Ej_Lk_B Heterogeneous_pk_Ej_L_Bk Heterogeneous_pk_Ej_Lk_Bk Heterogeneous_pk_Ek_L_B Heterogeneous_pk_Ek_Lk_B Heterogeneous_pk_Ek_L_Bk Heterogeneous_pk_Ek_Lk_Bk"""

# mixmodCompositeModel(variable.independency=T)
raw_composite_var_indep_true = """Heterogeneous_pk_E_L_B Heterogeneous_pk_E_Lk_B Heterogeneous_pk_E_L_Bk Heterogeneous_pk_E_Lk_Bk Heterogeneous_pk_Ek_L_B Heterogeneous_pk_Ek_Lk_B Heterogeneous_pk_Ek_L_Bk Heterogeneous_pk_Ek_Lk_Bk Heterogeneous_p_E_L_B Heterogeneous_p_E_Lk_B Heterogeneous_p_E_L_Bk Heterogeneous_p_E_Lk_Bk Heterogeneous_p_Ek_L_B Heterogeneous_p_Ek_Lk_B Heterogeneous_p_Ek_L_Bk Heterogeneous_p_Ek_Lk_Bk"""

# mixmodCompositeModel(variable.independency=F)
raw_composite_var_indep_false = """Heterogeneous_pk_Ekj_L_B Heterogeneous_pk_Ekj_Lk_B Heterogeneous_pk_Ekj_L_Bk Heterogeneous_pk_Ekj_Lk_Bk Heterogeneous_pk_Ekjh_L_B Heterogeneous_pk_Ekjh_Lk_B Heterogeneous_pk_Ekjh_L_Bk Heterogeneous_pk_Ekjh_Lk_Bk Heterogeneous_pk_Ej_L_B Heterogeneous_pk_Ej_Lk_B Heterogeneous_pk_Ej_L_Bk Heterogeneous_pk_Ej_Lk_Bk Heterogeneous_p_Ekj_L_B Heterogeneous_p_Ekj_Lk_B Heterogeneous_p_Ekj_L_Bk Heterogeneous_p_Ekj_Lk_Bk Heterogeneous_p_Ekjh_L_B Heterogeneous_p_Ekjh_Lk_B Heterogeneous_p_Ekjh_L_Bk Heterogeneous_p_Ekjh_Lk_Bk Heterogeneous_p_Ej_L_B Heterogeneous_p_Ej_Lk_B Heterogeneous_p_Ej_L_Bk Heterogeneous_p_Ej_Lk_Bk"""

# mixmodCompositeModel(component.independency=T)
raw_composite_comp_indep_true = """Heterogeneous_pk_E_L_B Heterogeneous_pk_E_Lk_B Heterogeneous_pk_E_L_Bk Heterogeneous_pk_E_Lk_Bk Heterogeneous_pk_Ej_L_B Heterogeneous_pk_Ej_Lk_B Heterogeneous_pk_Ej_L_Bk Heterogeneous_pk_Ej_Lk_Bk Heterogeneous_p_E_L_B Heterogeneous_p_E_Lk_B Heterogeneous_p_E_L_Bk Heterogeneous_p_E_Lk_Bk Heterogeneous_p_Ej_L_B Heterogeneous_p_Ej_Lk_B Heterogeneous_p_Ej_L_Bk Heterogeneous_p_Ej_Lk_Bk"""

# mixmodCompositeModel(component.independency=F)
raw_composite_comp_indep_false = """Heterogeneous_pk_Ekj_L_B Heterogeneous_pk_Ekj_Lk_B Heterogeneous_pk_Ekj_L_Bk Heterogeneous_pk_Ekj_Lk_Bk Heterogeneous_pk_Ekjh_L_B Heterogeneous_pk_Ekjh_Lk_B Heterogeneous_pk_Ekjh_L_Bk Heterogeneous_pk_Ekjh_Lk_Bk Heterogeneous_pk_Ek_L_B Heterogeneous_pk_Ek_Lk_B Heterogeneous_pk_Ek_L_Bk Heterogeneous_pk_Ek_Lk_Bk Heterogeneous_p_Ekj_L_B Heterogeneous_p_Ekj_Lk_B Heterogeneous_p_Ekj_L_Bk Heterogeneous_p_Ekj_Lk_Bk Heterogeneous_p_Ekjh_L_B Heterogeneous_p_Ekjh_Lk_B Heterogeneous_p_Ekjh_L_Bk Heterogeneous_p_Ekjh_Lk_Bk Heterogeneous_p_Ek_L_B Heterogeneous_p_Ek_Lk_B Heterogeneous_p_Ek_L_Bk Heterogeneous_p_Ek_Lk_Bk"""

# mixmodCompositeModel(component.independency=F, variable.independency=T)
raw_composite_ci_f_vi_t = """Heterogeneous_pk_Ek_L_B Heterogeneous_pk_Ek_Lk_B Heterogeneous_pk_Ek_L_Bk Heterogeneous_pk_Ek_Lk_Bk Heterogeneous_p_Ek_L_B Heterogeneous_p_Ek_Lk_B Heterogeneous_p_Ek_L_Bk Heterogeneous_p_Ek_Lk_Bk"""

# mixmodCompositeModel(component.independency=T, variable.independency=F)
raw_composite_ci_t_vi_f = """Heterogeneous_pk_Ej_L_B Heterogeneous_pk_Ej_Lk_B Heterogeneous_pk_Ej_L_Bk Heterogeneous_pk_Ej_Lk_Bk Heterogeneous_p_Ej_L_B Heterogeneous_p_Ej_Lk_B Heterogeneous_p_Ej_L_Bk Heterogeneous_p_Ej_Lk_Bk"""

# mixmodCompositeModel(component.independency=T, equal.proportions=F)
raw_composite_ci_t_eqp_f = """Heterogeneous_pk_E_L_B Heterogeneous_pk_E_Lk_B Heterogeneous_pk_E_L_Bk Heterogeneous_pk_E_Lk_Bk Heterogeneous_pk_Ej_L_B Heterogeneous_pk_Ej_Lk_B Heterogeneous_pk_Ej_L_Bk Heterogeneous_pk_Ej_Lk_Bk"""

# mixmodCompositeModel(component.independency=F, free.proportions=F)
raw_composite_ci_f_eqp_t = """Heterogeneous_p_Ekj_L_B Heterogeneous_p_Ekj_Lk_B Heterogeneous_p_Ekj_L_Bk Heterogeneous_p_Ekj_Lk_Bk Heterogeneous_p_Ekjh_L_B Heterogeneous_p_Ekjh_Lk_B Heterogeneous_p_Ekjh_L_Bk Heterogeneous_p_Ekjh_Lk_Bk Heterogeneous_p_Ek_L_B Heterogeneous_p_Ek_Lk_B Heterogeneous_p_Ek_L_Bk Heterogeneous_p_Ek_Lk_Bk"""

# mixmodCompositeModel(equal.proportions=T, free.proportions=F)
raw_composite_eqp_t_frp_f = """Heterogeneous_p_E_L_B Heterogeneous_p_E_Lk_B Heterogeneous_p_E_L_Bk Heterogeneous_p_E_Lk_Bk Heterogeneous_p_Ekj_L_B Heterogeneous_p_Ekj_Lk_B Heterogeneous_p_Ekj_L_Bk Heterogeneous_p_Ekj_Lk_Bk Heterogeneous_p_Ekjh_L_B Heterogeneous_p_Ekjh_Lk_B Heterogeneous_p_Ekjh_L_Bk Heterogeneous_p_Ekjh_Lk_Bk Heterogeneous_p_Ej_L_B Heterogeneous_p_Ej_Lk_B Heterogeneous_p_Ej_L_Bk Heterogeneous_p_Ej_Lk_Bk Heterogeneous_p_Ek_L_B Heterogeneous_p_Ek_Lk_B Heterogeneous_p_Ek_L_Bk Heterogeneous_p_Ek_Lk_Bk"""

# mixmodCompositeModel(equal.proportions=F, free.proportions=T)
raw_composite_eqp_f_frp_t = """Heterogeneous_pk_E_L_B Heterogeneous_pk_E_Lk_B Heterogeneous_pk_E_L_Bk Heterogeneous_pk_E_Lk_Bk Heterogeneous_pk_Ekj_L_B Heterogeneous_pk_Ekj_Lk_B Heterogeneous_pk_Ekj_L_Bk Heterogeneous_pk_Ekj_Lk_Bk Heterogeneous_pk_Ekjh_L_B Heterogeneous_pk_Ekjh_Lk_B Heterogeneous_pk_Ekjh_L_Bk Heterogeneous_pk_Ekjh_Lk_Bk Heterogeneous_pk_Ej_L_B Heterogeneous_pk_Ej_Lk_B Heterogeneous_pk_Ej_L_Bk Heterogeneous_pk_Ej_Lk_Bk Heterogeneous_pk_Ek_L_B Heterogeneous_pk_Ek_Lk_B Heterogeneous_pk_Ek_L_Bk Heterogeneous_pk_Ek_Lk_Bk"""


def to_set(models):
    return set([m.name for m in models])


class TestGaussianModels(unittest.TestCase):
    def setUp(self):
        self.all = set(raw_gaussian_all.split())
        self.spherical = set(raw_gaussian_spherical.split())
        self.diagonal = set(raw_gaussian_diagonal.split())
        self.spherical_diagonal = set(raw_gaussian_spherical_diagonal.split())
        self.general = set(raw_gaussian_general.split())
        self.equal_proportions = set(raw_gaussian_equal_proportions.split())
        self.free_proportions = set(raw_gaussian_free_proportions.split())

    def test_gaussian_default(self):
        model = mixmod.gaussian_model()
        self.assertTrue(model == [gm.ModelName.Gaussian_pk_Lk_C])

    def test_gaussian_all(self):
        models = mixmod.gaussian_model(gm.ALL)
        self.assertTrue(to_set(models) == self.all)

    def test_gaussian_spherical(self):
        models = mixmod.gaussian_model(family=gm.SPHERICAL)
        self.assertTrue(to_set(models) == self.spherical)

    def test_gaussian_diagonal(self):
        models = mixmod.gaussian_model(family=gm.DIAGONAL)
        self.assertTrue(to_set(models) == self.diagonal)

    def test_gaussian_general(self):
        models = mixmod.gaussian_model(family=gm.GENERAL)
        self.assertTrue(to_set(models) == self.general)

    def test_gaussian_spherical_diagonal(self):
        models = mixmod.gaussian_model(family=[gm.SPHERICAL, gm.DIAGONAL])
        self.assertTrue(to_set(models) == self.spherical_diagonal)

    def test_gaussian_equal_proportions(self):
        models = mixmod.gaussian_model(equal_proportions=True)
        self.assertTrue(to_set(models) == self.equal_proportions)

    def test_gaussian_free_proportions(self):
        models = mixmod.gaussian_model(equal_proportions=False)
        self.assertTrue(to_set(models) == self.free_proportions)


class TestMultinomialModels(unittest.TestCase):
    def setUp(self):
        self.all = set(raw_multinomial_all.split())
        self.equal_proportions = set(raw_multinomial_equal_proportions.split())
        self.free_proportions = set(raw_multinomial_free_proportions.split())
        self.var_indep_true = set(raw_multinomial_var_indep_true.split())
        self.var_indep_false = set(raw_multinomial_var_indep_false.split())
        self.comp_indep_true = set(raw_multinomial_comp_indep_true.split())
        self.comp_indep_false = set(raw_multinomial_comp_indep_false.split())
        self.ci_f_vi_t = set(raw_multinomial_ci_f_vi_t.split())
        self.ci_t_vi_f = set(raw_multinomial_ci_t_vi_f.split())
        self.ci_t_eqp_f = set(raw_multinomial_ci_t_eqp_f.split())
        self.ci_f_eqp_t = set(raw_multinomial_ci_f_eqp_t.split())
        self.eqp_t_frp_f = set(raw_multinomial_eqp_t_frp_f.split())
        self.eqp_f_frp_t = set(raw_multinomial_eqp_f_frp_t.split())

    def test_multinomial_default(self):
        model = mixmod.multinomial_model()
        self.assertTrue(model == [gm.ModelName.Binary_pk_Ekjh])

    def test_multinomial_all(self):
        models = mixmod.multinomial_model(gm.ALL)
        self.assertTrue(to_set(models) == self.all)

    def test_multinomial_equal_proportions(self):
        models = mixmod.multinomial_model(equal_proportions=True)
        self.assertTrue(to_set(models) == self.equal_proportions)

    def test_multinomial_free_proportions(self):
        models = mixmod.multinomial_model(equal_proportions=False)
        self.assertTrue(to_set(models) == self.free_proportions)

    def test_multinomial_var_indep_true(self):
        models = mixmod.multinomial_model(variable_independency=True)
        self.assertTrue(to_set(models) == self.var_indep_true)

    def test_multinomial_var_indep_false(self):
        models = mixmod.multinomial_model(variable_independency=False)
        self.assertTrue(to_set(models) == self.var_indep_false)

    def test_multinomial_comp_indep_true(self):
        models = mixmod.multinomial_model(component_independency=True)
        self.assertTrue(to_set(models) == self.comp_indep_true)

    def test_multinomial_comp_indep_false(self):
        models = mixmod.multinomial_model(component_independency=False)
        self.assertTrue(to_set(models) == self.comp_indep_false)

    def test_multinomial_comp_indep_false_var_indep_true(self):
        models = mixmod.multinomial_model(component_independency=False, variable_independency=True)
        self.assertTrue(to_set(models) == self.ci_f_vi_t)

    def test_multinomial_comp_indep_true_var_indep_false(self):
        models = mixmod.multinomial_model(component_independency=True, variable_independency=False)
        self.assertTrue(to_set(models) == self.ci_t_vi_f)

    def test_multinomial_comp_indep_false_equal_proportions_true(self):
        models = mixmod.multinomial_model(component_independency=False, equal_proportions=True)
        self.assertTrue(to_set(models) == self.ci_f_eqp_t)

    def test_multinomial_comp_indep_true_equal_proportions_false(self):
        models = mixmod.multinomial_model(component_independency=True, equal_proportions=False)
        self.assertTrue(to_set(models) == self.ci_t_eqp_f)

    def test_multinomial_eqp_t_frp_f(self):
        models = mixmod.multinomial_model(equal_proportions=True)
        self.assertTrue(to_set(models) == self.eqp_t_frp_f)

    def test_multinomial_eqp_f_frp_t(self):
        models = mixmod.multinomial_model(equal_proportions=False)
        self.assertTrue(to_set(models) == self.eqp_f_frp_t)


class TestCompositeModels(unittest.TestCase):
    def setUp(self):
        self.all = set(raw_composite_all.split())
        self.equal_proportions = set(raw_composite_equal_proportions.split())
        self.free_proportions = set(raw_composite_free_proportions.split())
        self.var_indep_true = set(raw_composite_var_indep_true.split())
        self.var_indep_false = set(raw_composite_var_indep_false.split())
        self.comp_indep_true = set(raw_composite_comp_indep_true.split())
        self.comp_indep_false = set(raw_composite_comp_indep_false.split())
        self.ci_f_vi_t = set(raw_composite_ci_f_vi_t.split())
        self.ci_t_vi_f = set(raw_composite_ci_t_vi_f.split())
        self.ci_t_eqp_f = set(raw_composite_ci_t_eqp_f.split())
        self.ci_f_eqp_t = set(raw_composite_ci_f_eqp_t.split())
        self.eqp_t_frp_f = set(raw_composite_eqp_t_frp_f.split())
        self.eqp_f_frp_t = set(raw_composite_eqp_f_frp_t.split())

    def test_composite_default(self):
        model = mixmod.composite_model()
        self.assertTrue(model == [gm.ModelName.Heterogeneous_pk_Ekjh_Lk_Bk])

    def test_composite_all(self):
        models = mixmod.composite_model(gm.ALL)
        self.assertTrue(to_set(models) == self.all)

    def test_composite_equal_proportions(self):
        models = mixmod.composite_model(equal_proportions=True)
        self.assertTrue(to_set(models) == self.equal_proportions)

    def test_composite_free_proportions(self):
        models = mixmod.composite_model(equal_proportions=False)
        self.assertTrue(to_set(models) == self.free_proportions)

    def test_composite_var_indep_true(self):
        models = mixmod.composite_model(variable_independency=True)
        self.assertTrue(to_set(models) == self.var_indep_true)

    def test_composite_var_indep_false(self):
        models = mixmod.composite_model(variable_independency=False)
        self.assertTrue(to_set(models) == self.var_indep_false)

    def test_composite_comp_indep_true(self):
        models = mixmod.composite_model(component_independency=True)
        self.assertTrue(to_set(models) == self.comp_indep_true)

    def test_composite_comp_indep_false(self):
        models = mixmod.composite_model(component_independency=False)
        self.assertTrue(to_set(models) == self.comp_indep_false)

    def test_composite_comp_indep_false_var_indep_true(self):
        models = mixmod.composite_model(component_independency=False, variable_independency=True)
        self.assertTrue(to_set(models) == self.ci_f_vi_t)

    def test_composite_comp_indep_true_var_indep_false(self):
        models = mixmod.composite_model(component_independency=True, variable_independency=False)
        self.assertTrue(to_set(models) == self.ci_t_vi_f)

    def test_composite_comp_indep_false_equal_proportions_true(self):
        models = mixmod.composite_model(component_independency=False, equal_proportions=True)
        self.assertTrue(to_set(models) == self.ci_f_eqp_t)

    def test_composite_comp_indep_true_equal_proportions_false(self):
        models = mixmod.composite_model(component_independency=True, equal_proportions=False)
        self.assertTrue(to_set(models) == self.ci_t_eqp_f)

    def test_composite_eqp_t_frp_f(self):
        models = mixmod.composite_model(equal_proportions=True)
        self.assertTrue(to_set(models) == self.eqp_t_frp_f)

    def test_composite_eqp_f_frp_t(self):
        models = mixmod.composite_model(equal_proportions=False)
        self.assertTrue(to_set(models) == self.eqp_f_frp_t)


class TestClustering(unittest.TestCase):
    def setUp(self):
        self.iris_train_data = pnd.read_csv(filepath_or_buffer='data/iris.train', sep=',', header=False)

    def test_gaussian_simple(self):
        cluster = mixmod.cluster(self.iris_train_data, [2, 3, 4], gm.QUANTITATIVE,
                                 models=mixmod.gaussian_model(family=gm.DIAGONAL))


if __name__ == '__main__':
    # unittest.main()
    # suite = unittest.TestLoader().loadTestsFromTestCase(TestGaussianModels)
    all_tests = unittest.TestSuite()
    all_tests.addTest(unittest.makeSuite(TestGaussianModels))
    all_tests.addTest(unittest.makeSuite(TestMultinomialModels))
    all_tests.addTest(unittest.makeSuite(TestCompositeModels))
    unittest.TextTestRunner(verbosity=2).run(all_tests)
