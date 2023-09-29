## ################################################################################
##     copyright            : (C) MIXMOD Team - 2001-2014
##     email                : contact@mixmod.org
## ################################################################################

## ################################################################################
##     This file is part of MIXMOD

##     MIXMOD is free software: you can redistribute it and/or modify
##     it under the terms of the GNU General Public License as published by
##     the Free Software Foundation, either version 3 of the License, or
##     (at your option) any later version.

##     MIXMOD is distributed in the hope that it will be useful,
##     but WITHOUT ANY WARRANTY; without even the implied warranty of
##     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
##     GNU General Public License for more details.

##     You should have received a copy of the GNU General Public License
##     along with MIXMOD.  If not, see <http://www.gnu.org/licenses/>.

##     All information available on : http://www.mixmod.org
## ################################################################################

##  @author: Christian Poli, INRIA

import scipy
import scipy.stats as st

def check_y_plot(y, data):
    _, nb_var = data.shape
    if isinstance(y, str) or not is_iterable(y):
        y = [y]
    if is_index_iter(y):
        for i in y:
            if i >= nb_var:
                raise ValueError("y indices mismatch the data dimension")
        return y
    elif not is_dataframe(data):
        raise ValueError("the data type must be dataframe when y is not an int array")
    y_int = []
    for elt in y:
        if elt not in data.columns:
            raise ValueError("y element {} is not a column in {}".
                             format(elt, data.columns))
        else:
            y_int.append(data.columns.get_loc(elt))
    if not len(y_int):
        raise ValueError("Void y")
    return y_int

def colnames (data):
    if  isinstance(data, pd.core.frame.DataFrame):
        return data.columns
    return [str(i) for i in range(data.shape[1])]
def get_data_ix(data):
    if  isinstance(data, pd.core.frame.DataFrame):
        return data.iloc
    return data



from matplotlib.lines import Line2D
markers = Line2D.filled_markers + ('+',)

len_markers = len(markers)

favorite_colors = ['red', 'blue', 'magenta', 'orange', 'grey', 'yellow', 'black']
colors = list(matplotlib.colors.cnames.keys())
customized_colors = favorite_colors + [c for c in colors if c not in favorite_colors]

def get_marker(i):
        return str(markers[i % len_markers])

def get_color(i, colors_=None):
    color_list = customized_colors
    if colors_:
        if i < len(colors_):
            return str(colors_[i])
        else:
            print("This display operation requires more than {} colors."
                  "The provided color set will be completed with default values".format(len(colors_)))
            color_list = colors_ + [c for c in color_list if c not in colors_]
    sz = len(color_list)
    return str(color_list[(i % sz)])

def draw_ellipse(plt_obj, best_result, i, j, **kwargs):
    """
    ...
    """
    angles = np.linspace(0, 2*np.pi, num=200)
    par = best_result.parameters
    nb_cluster = best_result.nb_cluster
    for k in range(nb_cluster):
        mean_k = par.mean[k]
        ctr = [mean_k[i], mean_k[j]]
        var_k = par.variance[k]
        mx = np.array([[var_k[i, i], var_k[j, i]], [var_k[i, j], var_k[j, j]]])
        eig_val, eig_vec = np.linalg.eig(mx)
        eig_scl = np.dot(eig_vec, np.diag(np.sqrt(eig_val)))
        x_mat = np.array([ctr[0] - eig_scl[0,:], ctr[0] + eig_scl[0,:]])
        y_mat = np.array([ctr[1] - eig_scl[1,:], ctr[1] + eig_scl[1,:]])
        ell_base = np.array([np.sqrt(eig_val[0])*np.cos(angles), np.sqrt(eig_val[1])*np.sin(angles)])
        ell_rot = np.dot(eig_vec, ell_base)
        x_stuff = ctr[0] - ell_rot[0]
        y_stuff = ctr[1] - ell_rot[1]
        plt_obj.plot(x_stuff, y_stuff, markersize=5, color='red') #, linestyle='--')
        plt_obj.plot(x_mat[:,0], y_mat[:,0], markersize=7, color='black', linestyle='--')
        plt_obj.plot(x_mat[:,1], y_mat[:,1], markersize=7, color='black', linestyle='--')
        plt_obj.plot(ctr[0], ctr[1], marker='x', markersize=5,markeredgewidth=3.0, color='blue', linestyle='--')

def plot_cluster(plt_obj, best_result, data, x_var=0, y_var=1, colors=None, with_ellipse=True, **kwargs):
    plt_obj.tick_params(axis='both', which='major', labelsize=8)
    plt_obj.tick_params(axis='both', which='minor', labelsize=6)
    partition = best_result.partition
    nb_cluster = best_result.nb_cluster
    cols = colnames(data)
    x_lib = kwargs.get('x_lib',cols[x_var])
    y_lib = kwargs.get('y_lib',cols[y_var])
    data_ix = get_data_ix(data)
    for i in range(nb_cluster):
        x_stuff = []
        y_stuff = []
        for p, x_, y_ in zip(partition, data_ix[:, x_var], data_ix[:, y_var]):
            if p==i+1:
                x_stuff.append(x_)
                y_stuff.append(y_)
        plt_obj.plot(x_stuff, y_stuff, marker=get_marker(i),  markerfacecolor='none', markersize=7, markeredgecolor=get_color(i, colors), linestyle='',**kwargs)
    if with_ellipse:
        draw_ellipse(plt_obj, best_result, x_var, y_var)



def hist_cluster_var(plt_obj, best_result, data, var,  bins=10, hist_x_dim=10000, **kwargs):
    plt_obj.tick_params(axis='both', which='major', labelsize=8)
    plt_obj.tick_params(axis='both', which='minor', labelsize=6)
    _, nb_var = data.shape
    data_ix = get_data_ix(data)
    nb_cluster = best_result.nb_cluster
    par = best_result.parameters
    cols = colnames(data)
    x_axis = np.linspace(min(data_ix[:, var]),max(data_ix[:, var]),num=hist_x_dim)
    density = np.empty([nb_cluster, len(x_axis)],dtype=float)
    for k in range(nb_cluster):
        density[k] = par.proportions[k]*st.norm.pdf(x_axis,loc=par.mean[k][var],scale=np.sqrt(par.variance[k][var,var]))
    mixture = density.sum(axis=0)
    n, bins, patches = plt_obj.hist(np.array(data_ix[:, var]), bins=bins, **kwargs)
    ratio = max(n)/max(mixture)
    density = density * ratio
    mixture = mixture * ratio
    plt_obj.plot(x_axis, mixture, color=colors[0])
    plt_obj.set_title('Histogram of {}'.format(cols[var]))
    for k in range(nb_cluster):
        plt_obj.plot(x_axis, density[k], color=colors[k+1], linestyle='--',**kwargs)

def barplot_cluster(self_, variables=None, colors=None, verbose=False, show=True, criterion=None, **kwargs):
    data = self_.data
    best_result = self_.get_best_result(criterion)
    nb_cluster = best_result.nb_cluster
    par = best_result.parameters
    nb_sample, nb_var = data.shape
    if self_.data_type != gm.QUALITATIVE:
        raise ValueError("data must contain only qualitative variables!")
    if variables is not None:
        variables = check_y_plot(variables, data)
    else:
        variables = list(range(nb_var))
    nb_sel_var = len(variables)
    if not nb_sel_var:
        raise ValueError("'variables' is empty!")
    if nb_sel_var < 4:
        plot_col = nb_sel_var
        plot_row = 1
    else:
        plot_col = int(np.floor(np.sqrt(nb_sel_var)))
        if nb_sel_var > plot_col**2:
            plot_row = plot_col + 1
        else:
            plot_row = plot_col
    fig, plt_array = plt.subplots(plot_row, plot_col) if plot_row>1 or plot_col>1 else plt.subplots(1)
    def get_plt_obj(i, j):
        if plot_row>1 and plot_col>1:
            return plt_array[i][j]
        if plot_row==1 and plot_col==1:
            return plt_array
        return plt_array[j]
    for iv, v in enumerate(variables):
        fact = par.factor[v]
        t=pd.pivot_table(data, columns=[data.columns[v]],aggfunc=len)
        proba = np.empty(shape=(nb_cluster,fact))
        for k in range(nb_cluster):
            center_k = par.center[k, v]-1
            proba_k = copy.deepcopy(par.scatter[k][v,:])
            proba_k[center_k] = 1 - proba_k[center_k]
            proba[k] = proba_k[:fact]
        # plot
        i = int(iv // plot_col)
        j = iv % plot_col
        pltobj = get_plt_obj(i,j)
        legend_ = []
        rect_x = None
        rect_y = np.zeros(fact)
        xticks_ = []
        xticklabels_ = []
        width_ = 1.0 / (nb_cluster + 1)
        for k in range(nb_cluster):
            height = proba[k]
            #left = np.linspace(1, 2*len(height)+1,num=1)
            nb_bar = len(height)
            left=np.arange(nb_bar) + k*width_
            b = pltobj.bar(left,height, width=width_, color=get_color(k, colors), **kwargs)
            k_labels = ['C{}'.format(k+1),] * nb_bar
            xticklabels_.extend(k_labels)
            if rect_x is None:
                rect_x = [r.get_x() for r in b]
            mid_ = [r.get_x()+r.get_width()/2.0 for r in b]
            xticks_.extend(mid_)
            legend_.append("Cluster {}".format(k))
        pltobj.set_xticks(xticks_, minor=False)
        pltobj.set_xticklabels(xticklabels_, fontdict=None, minor=False)

        for f in range(fact):
            y_ = t.iloc[0,f]/float(nb_sample)
            x = rect_x[f]
            pl=pltobj.plot([x, x + width_*nb_cluster], [y_, y_], markersize=7, label="Unconditional frequency", color='red', linestyle='--')
            if not f:
                pass
                # pltobj.annotate('Unconditional frequency',xy=(x, y_),xytext=(0,5),textcoords='offset points',fontsize='xx-small',va='top')
            y_max = max(proba[:,f])
            if verbose:
                pltobj.annotate(t.columns[f],xy=(x+0.1*nb_cluster, y_max),xytext=(0,8),textcoords='offset points',fontsize='x-small',va='top',ha='left')
        pltobj.set_ylabel('Conditional frequency',fontsize='xx-small')
        pltobj.set_title('Barplot of {}'.format(data.columns[v]))
    for m in range(nb_sel_var, plot_row * plot_col):
        i = plot_row * plot_col // nb_sel_var
        j = plot_row * plot_col % nb_sel_var
        get_plt_obj(-i,j).axis('off')
    plt.gcf().canvas.manager.set_window_title('Multinomial variables')
    if show:
        plt.show()
    return fig
