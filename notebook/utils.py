from matplotlib.dates import MonthLocator, YearLocator, DateFormatter
from matplotlib.ticker import FuncFormatter
from datetime import date
import pylab

def set_plot_size(width, height):
    pylab.rcParams['figure.figsize'] = [width, height]

def set_default_plot_size():
    set_plot_size(width=12, height=8)


def to_datetime(d):
    return date(d.year(), d.month(), d.dayOfMonth())

def format_rate(r, digits=2):
    format = '%.' + str(digits) + 'f %%'
    return format % (r*100.0)

def locator(span):
    if span < 400:
        return MonthLocator()
    elif 400 <= span < 800:
        return MonthLocator(bymonth=[1,4,7,10])
    elif 800 <= span < 3700:
        return YearLocator()
    else:
        return YearLocator(5)
    
def plot_curve(plt,dates,rates,ymin=None,ymax=None,digits=2):
    span = dates[-1] - dates[0]
    fig, ax = plt.subplots()
    dates = [ to_datetime(d) for d in dates ]
    for (rs, style) in rates:
        ax.plot_date(dates, rs, style)
    ax.set_xlim(min(dates),max(dates))
    ax.xaxis.set_major_locator(locator(span))
    ax.xaxis.set_major_formatter(DateFormatter("%b '%y"))
    ax.autoscale_view()
    ax.xaxis.grid(True, 'major')
    ax.xaxis.grid(False, 'minor')
    ax.set_ylim(ymin,ymax)
    ax.yaxis.set_major_formatter(
        FuncFormatter(lambda r,pos: format_rate(r,digits)))
    fig.autofmt_xdate()
    plt.show()
